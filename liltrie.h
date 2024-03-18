#ifndef LILTRIE_H
#define LILTRIE_H

#include <cstdlib>   // for drand48, srand48
#include <iostream>
#include <ios>
#include <iomanip>
#include <string>
#include <vector>
#include <chrono>

#include "random220.h"

/***
 * Randomly partition the elements of vector src into two other vectors tru(e)
 * and fals(e) based on the probability.  
 *
 * probability=0.5 => about a 50-50 split.
 * probability=0.10 => tru will * have (about) 10% of the elements, fals about * 90%.
 */
template< typename T >
void partition_vector( double probability, std::vector<T>& src, std::vector<T>& tru, std::vector<T>& fals )
{
	for( auto &e: src ) {
		if( bernoulli(probability) ) {
			tru.push_back(e);
		} else {
			fals.push_back(e);
		}
	}
}

static const size_t STATIC_SIZE_LIMIT=2000;

/***
 * Test .insert, .finalize, .contains for the trie class Y.
 *
 * If sample==false || dict.size() < STATIC_SIZE_LIMIT, all the words in the
 * dictionary are used.  Otherwise, a random number of words are put in the
 * trie, but *all* dictionary words are tested with .contains()
 *
 * Word insertion and word testing order are always randomized.
 */
template <typename Y>
void test_node_functions( Y& trie, std::vector<std::string>& dict, bool sample = false )
{
	fisher_yates( dict );
	std::vector<std::string> outwords;
	std::vector<std::string> inwords;
	double sample_prob = (sample && dict.size()>STATIC_SIZE_LIMIT ) ? 0.5 : 1 ;
	partition_vector( sample_prob, dict, inwords, outwords );

	for( auto const &s: inwords ) {
	  	trie.insert(s);
	}
	trie.finalize();

	std::cout << "size (number of words) " << trie.size() << ", ";
	std::cout << "descendents (number of nodes) " << trie.descendents() << std::endl;

	// shuffle again, so they aren't in the same order as they were added to trie
	fisher_yates( inwords );
	for( auto const &s: inwords ) {
		if( !trie.contains( s ) ) {
			std::cerr << "error: string " << s << " should be in trie, but .contains() says false." << std::endl;
			::exit(1);
		}
	}

	// outwords has already been suffled
	for( auto const &s: outwords ) {
		if( trie.contains( s ) ) {
			std::cerr << "error: string " << s << " should NOT be in trie, but .contains() says true." << std::endl;
			::exit(1);
		}
	}
}

/***
 * Value and print a count and population fraction histogram of the number
 * of children per node in a trie.  Results (if show==true) are on std::cerr.
 *
 * use sample_size=COLLECT_CH_FULLSIZE to test with all dict words
 * use sample_size=COLLECT_CH_RANDOMSIZE to pick a random number of words >1 to test
 * use any other value of sample_size to specify a precise number of words
 */
enum collect_ch_samplesize {
	COLLECT_CH_FULLSIZE,    // all words
	COLLECT_CH_RANDOMSIZE,  // random # of words 
    COLLECT_CH_SAMPLESIZES, };
template< typename Y >
void collect_child_histogram( Y& trie, std::vector<std::string>& dict, std::vector<size_t>& histo, 
		size_t sample_size=1, bool show=true )
{
	switch( sample_size ) {
		case COLLECT_CH_FULLSIZE :
			sample_size = dict.size();
			break;
		case COLLECT_CH_RANDOMSIZE:
			sample_size = equalikely(2,dict.size());
			// fall through - fisher_yates does our sampling
		case COLLECT_CH_SAMPLESIZES :  // make compilers be quiet about missing SAMPLESIZES
		default :
			fisher_yates( dict, sample_size );
			break;	
	}

	for( size_t i=0; i<sample_size; ++i ) {
  		trie.insert(dict[i]);
	}
	trie.finalize();

	for( size_t i=0; i<histo.size(); ++i ) {
		histo[i] = 0;
	}

	trie.children_histogram( histo );

	if( !show ) return;

	using namespace std;
	ios_base::fmtflags flags( cerr.flags() );
	double sum=0;
	int cols=0;
	/** show the raw counts */
 	for( size_t i=0; i<histo.size(); ++i ) {
		cerr << right << setw(2) << i << ": " << setw(6) << left << histo[i] << " ";
		sum += histo[i];
		if( !(++cols % 4 )) cerr << endl;
	}
	cerr << endl;
	cols=0;
	std::vector<double> fx(histo.size(),0);
	/* show the frequency data */
 	for( size_t i=0; i<histo.size(); ++i ) {
		fx[i] = histo[i] / sum;
		cerr << right << setw(2) << i << ": " << setw(6) << setprecision(4) << fixed << fx[i] << " ";
		if( !(++cols % 4 )) cerr << endl;
	}
	cerr << endl;
	cerr.flags( flags );
}


/***
 * Helper function of time_trials<>, runs a time trial for just one trie.
 */
template <typename T>
std::chrono::duration<double> 
	one_time_trial( const long trie_size, T& trie, std::vector<std::string>& words, bool finalize )
{
    auto start_time = std::chrono::system_clock::now(); 
	// every other one into the trie
	for( long i=0; i<trie_size; i+=2 ) {
		trie.insert( words[i] );
	}
	// reset timer if using finalize (!on_the_fly) 
	if( finalize ) {
		trie.finalize();
		start_time = std::chrono::system_clock::now(); 
	}

   	for( long i=0; i<trie_size; i+=2 ) {
		// first of two must be in the trie
		if( !trie.contains( words[i] ) ) {
			std::cerr << "error: trie .contains(\"" << words[i] << "\") failure "
				"(!contains() when it should --- back to testing?" << std::endl;
			::exit(1);
		}
		// second of two is not in the trie
		if( trie.contains( words[i+1] ) ) {
			std::cerr << "error: trie .contains(\"" << words[i] << "\") failure "
				"(contains() when it does not --- back to testing?" << std::endl;
			::exit(1);
		}
		trie.contains(words[i]);
	}
    auto stop_time = std::chrono::system_clock::now(); 
    return stop_time - start_time; 
}

/***
 * Run a time trial between two tries.  Results are in a std::pair with .first
 * being the time for trie type Y, .second being for trie type O.
 *
 * Provide empty tries to the function.
 * 
 * If finalize is true, timings ignore insertion times and report only the
 * times required for word queries.  Use this if you haven't implemented
 * "on-the-fly" compressed trie nodes.
 */
template< typename Y, typename O >
std::pair<std::chrono::duration<double>,std::chrono::duration<double>> 
	time_trials( Y& trie, O& opt, std::vector<std::string>& dict, bool finalize = true )
{
	long trie_size = equalikely(1, dict.size());
	// shuffle the first trie_size elements
	fisher_yates( dict, trie_size );
	std::chrono::duration<double> Y_speed, O_speed;
	if( bernoulli(0.5) ) {
		// Y goes first this time
		Y_speed = one_time_trial( trie_size, trie, dict, finalize);
		O_speed = one_time_trial( trie_size, opt, dict, finalize );
	} else {
		// O goes first
		O_speed = one_time_trial( trie_size, opt, dict, finalize );
		Y_speed = one_time_trial( trie_size, trie, dict, finalize );
	}
	return std::pair<std::chrono::duration<double>,std::chrono::duration<double>>(Y_speed, O_speed );
}

#endif // LILTRIE_H
