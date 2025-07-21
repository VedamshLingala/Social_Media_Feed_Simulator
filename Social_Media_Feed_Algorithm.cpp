#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <unordered_set>
#include <algorithm>
using namespace std;

// Structure for a Post
struct Post {
    int id;
    int userId;
    string content;
    int likes;
    int comments;
    int timestamp;

    Post(int id, int userId, string content, int timestamp)
        : id(id), userId(userId), content(content), likes(0), comments(0), timestamp(timestamp) {}
};

// Graph-based relationships between users
class SocialGraph {
public:
    map<int, unordered_set<int>> friendships;

    void addFriendship(int userA, int userB) {
        friendships[userA].insert(userB);
        friendships[userB].insert(userA);
    }

    const unordered_set<int>& getFriends(int userId) {
        return friendships[userId];
    }
};

// Social Media Feed Algorithm
class SocialMediaFeed {
private:
    vector<Post> posts;
    SocialGraph graph;

    struct PostScore {
        int score;
        Post post;

        bool operator<(const PostScore& other) const {
            return score < other.score;
        }
    };

public:
    void addPost(int userId, string content, int timestamp) {
        posts.emplace_back(posts.size(), userId, content, timestamp);
    }

    void addFriendship(int userA, int userB) {
        graph.addFriendship(userA, userB);
    }

    void likePost(int postId) {
        if (postId >= 0 && postId < posts.size()) {
            posts[postId].likes++;
        } else {
            cout << "Invalid Post ID. Please try again.\n";
        }
    }

    void commentOnPost(int postId) {
        if (postId >= 0 && postId < posts.size()) {
            posts[postId].comments++;
        } else {
            cout << "Invalid Post ID. Please try again.\n";
        }
    }

    vector<Post> getFeed(int userId) {
        priority_queue<PostScore> pq;

        for (const Post& post : posts) {
            int score = 0;

            // Base score from interactions
            score += post.likes * 10;
            score += post.comments * 20;

            // Bonus if post is from a friend
            if (graph.getFriends(userId).count(post.userId)) {
                score += 50;
            }

            // Recency bonus (smaller timestamps are older)
            score += max(0, 100 - (currentTime() - post.timestamp));

            pq.push({score, post});
        }

        vector<Post> feed;
        while (!pq.empty() && feed.size() < 10) { // Top 10 posts
            feed.push_back(pq.top().post);
            pq.pop();
        }
        return feed;
    }

    void displayFeed(const vector<Post>& feed, int userId) {
        if (feed.empty()) {
            cout << "No posts available for User " << userId << ".\n";
        } else {
            cout << "\n--- Feed for User " << userId << " ---\n";
            for (const Post& post : feed) {
                cout << "Post ID: " << post.id
                     << ", User ID: " << post.userId
                     << ", Content: " << post.content
                     << ", Likes: " << post.likes
                     << ", Comments: " << post.comments
                     << endl;
            }
        }
    }

    void displayInstructions() {
        cout << "Enter 1 to Add Friendship\n";
        cout << "Enter 2 to Add a Post\n";
        cout << "Enter 3 to Like a Post\n";
        cout << "Enter 4 to Comment on a Post\n";
        cout << "Enter 5 to Get User Feed\n";
        cout << "Enter 0 to Display Instructions\n";
        cout << "Enter -1 to Exit the Program\n";
    }

private:
    int currentTime() {
        return 1000; // Simulate a constant current time for simplicity
    }
};

int main() {
    SocialMediaFeed smFeed;

    cout << "Welcome to the Social Media Simulation!\n";
    smFeed.displayInstructions();

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    while (choice != -1) {
        switch (choice) {
            case 0:
                smFeed.displayInstructions();
                break;
            case 1: {
                int userA, userB;
                cout << "Enter two user IDs to create a friendship: ";
                cin >> userA >> userB;
                smFeed.addFriendship(userA, userB);
                cout << "Friendship added successfully!\n";
                break;
            }
            case 2: {
                int userId, timestamp;
                string content;
                cout << "Enter User ID: ";
                cin >> userId;
                cout << "Enter Post Content: ";
                cin.ignore();
                getline(cin, content);
                cout << "Enter Timestamp: ";
                cin >> timestamp;
                smFeed.addPost(userId, content, timestamp);
                cout << "Post added successfully!\n";
                break;
            }
            case 3: {
                int postId;
                cout << "Enter Post ID to like: ";
                cin >> postId;
                smFeed.likePost(postId);
                break;
            }
            case 4: {
                int postId;
                cout << "Enter Post ID to comment on: ";
                cin >> postId;
                smFeed.commentOnPost(postId);
                break;
            }
            case 5: {
                int userId;
                cout << "Enter User ID to get the feed for: ";
                cin >> userId;
                vector<Post> feed = smFeed.getFeed(userId);
                smFeed.displayFeed(feed, userId);
                break;
            }
            default:
                cout << "Invalid choice! Please try again.\n";
        }

        cout << "\nEnter your choice: ";
        cin >> choice;
    }

    cout << "Thank you for using the Social Media Simulation!\n";
    return 0;
}
