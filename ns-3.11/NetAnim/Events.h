// Manage future events for the Network Animator
// George F. Riley, Georgia Tech, Spring 2009

#ifndef __EVENTS_H__
#define __EVENTS_H__

#include <deque>
#include <string>
#include <fstream>

#include "NetModel.h"

// Define a type for a timestamped time/string pair
typedef std::pair<Time_t, std::string> TSPair_t;
// We can use a deque instead of a sorted container (map) since
// all events naturally come in timestamp order.
typedef std::deque<TSPair_t>     TSDeq_t;

void SetEventsFileHandle(int h);

void AddEventsFromFile(std::ifstream&); // Read the file and add events

int ProcessAllPending(NetModel*, Time_t); // Process all events with TS <= t

void AddEvent(Time_t t, const std::string& s); // Add a new event

Time_t GetEventTime(const std::string& s); // Get the event time from the string

Time_t EarliestEventTime(); // Get time of earliest event

TSPair_t GetEarliestEvent(); // Get and remove earliest event

void ProcessEvent(NetModel* m, const TSPair_t& e); // Parse and process an event

#endif

