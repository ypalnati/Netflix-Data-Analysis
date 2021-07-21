#pragma once

#include <iostream>
#include <set>
#include <iterator>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include "make_graph.h"
#include <thread>
#include<mutex>
using namespace std;
map<int, User*> userMap;
map<int, Movie*> movieMap;
map<int, int> customerIds;

int userCount=0;
std::mutex mtx1;
std::mutex mtx2;

void populateGraph(Graph g, ofstream& outfile)
{
    g.printGraph(outfile);

    outfile << "\n -------------------------------------------- \n";
    outfile << "\n Following are connected components \n";
   g.connectedComponents(outfile); // or can call g.connectedComponentsCount(outfile) to print connected componenets count at each level not the elements.
    outfile << "\n -------------------------------------------- \n";
    outfile << "\n finding cycle\n";
    g.one_cycle(outfile);
    outfile << "\n --------------shortest path------------------------------ \n";

    int start = 1;
    g.DijkstraSP(start, outfile);
    

}
//it will read the file and process the data
void reader1(string filename)
{
    ifstream MyFile(filename);
    string line;
    int current_movie = 0;

    while (getline(MyFile, line)) {
        if (line.back() == ':') {
            //if : is found in line which means it is a movie row we update the current_movie
            line.pop_back();
            stringstream temp(line);
            current_movie = 0;
            temp >> current_movie;
        }
        else {
            int user_id = 0, rating = 0;
            char date[15] = { '\0' };
            int year, dd, mm;
            //else extract all the values and if passes thecriteria we insert in the map
            sscanf_s(line.c_str(), "%d,%d,%s", &user_id, &rating, date, sizeof(date));
            sscanf_s(date, "%d-%d-%d", &year, &mm, &dd);
            if (year < 2005)
                continue;    
            if (rating < 4)
                continue;
            int review_key = current_movie * 10 + rating;

            mtx1.lock();
            if (userMap.find(user_id) == userMap.end()) {
                userMap[user_id] = new User(user_id);
            }
            //cout << current_movie << " " << user_id << " " << rating << " " << date << endl;
            userMap[user_id]->add_review(review_key);
            mtx1.unlock();

        }
    }
    
}
void reader3(string filename)
{
    ifstream MyFile(filename);
    string line;
    int current_movie = 0;

    while (getline(MyFile, line)) {
        if (line.back() == ':') {
            line.pop_back();
            stringstream temp(line);
            current_movie = 0;
            temp >> current_movie;
        }
        else {
            int user_id = 0, rating = 0;
            char date[15] = { '\0' };
            int year, dd, mm;
            sscanf_s(line.c_str(), "%d,%d,%s", &user_id, &rating, date, sizeof(date));
            sscanf_s(date, "%d-%d-%d", &year, &mm, &dd);
            if (year < 2005)
                continue;
            
          //criteria is same day same movie so storing those fields as unique key
            unsigned long int review_key = current_movie * 10000+ year * 10000 + mm * 100+ dd;

            mtx1.lock();
            if (userMap.find(user_id) == userMap.end()) {
                userMap[user_id] = new User(user_id);
            }
            //cout << current_movie << " " << user_id << " " << rating << " " << date << endl;
            userMap[user_id]->add_review(review_key);
            mtx1.unlock();

        }
    }

}
void reader2(string filename)
{
    ifstream MyFile(filename);
    string line;
    int current_movie = 0;

    while (getline(MyFile, line)) {
        if (line.back() == ':') {
            line.pop_back();
            stringstream temp(line);
            current_movie = 0;
            temp >> current_movie;

        }
        else {

            int user_id = 0, rating = 0;
            char date[15] = { '\0' };
            int year, dd, mm;
            sscanf_s(line.c_str(), "%d,%d,%s", &user_id, &rating, date, sizeof(date));
            sscanf_s(date, "%d-%d-%d", &year, &mm, &dd);

        
            if (rating != 5)
                continue;

            mtx1.lock();
            //storing customers in a map to get the index values of customers
            if (customerIds.find(user_id) == customerIds.end())
            {
                customerIds[user_id] = userCount;
                userCount++;
            }
            
            //for each movie storing all the customers who rated 5
            if (movieMap.find(current_movie) == movieMap.end()) {
                movieMap[current_movie] = new Movie(current_movie);
            }
            //cout << current_movie << " " << user_id << " " << rating << " " << date << endl;
            movieMap[current_movie]->add_user(user_id);
            mtx1.unlock();

        }
    }



}
void adjacencyCriteria3()
{
    //thread t1(reader1, "D:\\AOA\\assignment\\final\\data.txt");
    thread t1(reader3, "D:\\ratings_data_1.txt");
    thread t2(reader3, "D:\\ratings_data_2.txt");
    thread t3(reader3, "D:\\ratings_data_3.txt");
    thread t4(reader3, "D:\\ratings_data_4.txt");

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    vector <User*> v;
    for (map<int, User*>::iterator it = userMap.begin(); it != userMap.end(); ++it) {
        v.push_back(it->second);
    }
    Graph g(v.size());
    int itr, ktr;

    //criteria is to iterate all the customers and relate customers who went to  atleast one movie on same day 
    for (itr = 0; itr < v.size(); itr++)
    {
        for (ktr = itr + 1; ktr < v.size(); ktr++)
        {
            if (v[itr]->add_if_match(v[ktr], 1)) {
                g.addEdge(itr, ktr);
            }
        }
    }
    std::ofstream outfile;
    outfile.open("d:\\netflixtest3.txt", std::ios_base::app);
    populateGraph(g, outfile);
    userMap.clear();
}
void adjacencyCriteria1()
{
    //thread t1(reader1, "D:\\AOA\\assignment\\final\\data.txt");
    thread t1(reader1, "D:\\ratings_data_1.txt");
    thread t2(reader1, "D:\\ratings_data_2.txt");
    thread t3(reader1, "D:\\ratings_data_3.txt");
    thread t4(reader1, "D:\\ratings_data_4.txt");

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    vector <User*> v;
    for (map<int, User*>::iterator it = userMap.begin(); it != userMap.end(); ++it) {
        v.push_back(it->second);
    }
    Graph g(v.size());
    int itr, ktr;
    
    //criteria is to iterate all customers with each other and relate them if they have given same rating atleast for 4 movies (and above 4 rating)
    for (itr = 0; itr < v.size(); itr++)
    {
        for (ktr = itr + 1; ktr < v.size(); ktr++)
        {
            if (v[itr]->add_if_match(v[ktr], 4)) {
                g.addEdge(itr, ktr);
            }
        }
    }
    std::ofstream outfile;
    outfile.open("d:\\netflixtest1.txt", std::ios_base::app);
    populateGraph(g,outfile);
    userMap.clear();
}
void adjacencyCriteria2()
{
    //thread t1(reader2, "D:\\AOA\\assignment\\final\\data.txt");
    thread t1(reader2, "D:\\ratings_data_1.txt");
    thread t2(reader2, "D:\\ratings_data_2.txt");
    thread t3(reader2, "D:\\ratings_data_3.txt");
    thread t4(reader2, "D:\\ratings_data_4.txt");

    t1.join();
   t2.join();
    t3.join();
    t4.join();

    cout << "completed reading data" << endl;

    Graph g(customerIds.size());

    vector <Movie*> v;
    //criteria is to iterate each movie liked customers (rating=5) and add an edge between them
    //which means adding an edge if atleast one movie is in common
    for (map<int, Movie*>::iterator it = movieMap.begin(); it != movieMap.end(); ++it)
    {
        vector<int> matches = it->second->users;
        for (int itr = 0; itr < matches.size(); itr++)
        {
            for (int jtr = itr+1; jtr < matches.size(); jtr++)
            {
                g.addEdge(customerIds[matches[itr]], customerIds[matches[jtr]]);
                
           }
        }

    } 

    cout << "completed adding edges" << endl;
    std::ofstream outfile;
    outfile.open("d:\\netflixtest2.txt", std::ios_base::app);
    populateGraph(g,outfile);

    movieMap.clear();
}
