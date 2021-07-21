#include"Graph.h"
#include<mutex>
#include <thread>

struct Counter
{
    struct value_type { template<typename T> value_type(const T&) { } };
    void push_back(const value_type&) { ++count; }
    size_t count = 0;
};

void populateGraph(Graph g,ofstream& outfile);
void adjacencyCriteria1();
void adjacencyCriteria2();
void adjacencyCriteria3();


class Movie {
public:
    int movie_id;
    vector<int> users;
    Movie(int id) {
        movie_id = id;
    }

    void add_user(int userid)
    {
        users.push_back(userid);
    }

};
class User {
public:
    int user_id;
    vector<unsigned long int> reviews;

    User(int id) {
        user_id = id;
    }

    void add_review(int review)
    {
        reviews.push_back(review);
    }

    vector<User*> related_users;

    //Returns true if it finds minCount intersections between 2 customer reviews
    bool add_if_match(User* new_user, int minCount) {
        Counter c;
        std::sort(reviews.begin(), reviews.end());
        std::sort(new_user->reviews.begin(), new_user->reviews.end());
        set_intersection(reviews.begin(), reviews.end(), new_user->reviews.begin(), new_user->reviews.end(), std::back_inserter(c));
        if (c.count >= minCount)
        {
            return true;
        }
        return false;
    }

};

