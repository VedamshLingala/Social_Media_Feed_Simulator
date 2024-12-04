# Social Media Feed Simulation Project

---

## **Detailed Code Description**

### **Overview**
This project implements a simulation of a social media feed using core C++ data structures and algorithms. The program allows users to create posts, interact with them, establish friendships, and view a personalized feed based on interactions and relationships.

---

### **Code Components**

#### 1. **Data Structures Used**
- **`struct Post`**
  - Represents individual posts created by users.  
  - Attributes:  
    - `id`: Unique identifier for the post.  
    - `userId`: ID of the user who created the post.  
    - `content`: Text content of the post.  
    - `likes`: Number of likes the post has received.  
    - `comments`: Number of comments the post has received.  
    - `timestamp`: The time the post was created, used for feed recency prioritization.  

- **`class SocialGraph`**
  - A graph-based structure to manage friendships between users.  
  - **Data Structure Used:**
    - `map<int, unordered_set<int>> friendships`:  
      - Key: User ID.  
      - Value: Set of IDs representing the user's friends.  
  - **Purpose:** Allows efficient lookup and storage of user relationships.

- **`class SocialMediaFeed`**
  - Central class managing posts, friendships, and feed generation.  
  - **Key Components:**
    - **Posts Storage:**
      - `vector<Post> posts`: Stores all posts sequentially. Allows efficient addition and traversal of posts.
    - **Friendship Management:**
      - Uses the `SocialGraph` class for storing and retrieving user relationships.
    - **Feed Prioritization:**
      - Uses a **priority queue** (`priority_queue<PostScore>`) to rank posts based on calculated scores.

---

#### 2. **Core Functions**

- **Friendship Management**
  - `void addFriendship(int userA, int userB)`
    - Establishes a bidirectional friendship by adding each user to the other's `unordered_set`.  

- **Post Management**
  - `void addPost(int userId, string content, int timestamp)`
    - Adds a new post to the `posts` vector with the specified user, content, and timestamp.  

- **Interaction with Posts**
  - `void likePost(int postId)`
    - Increments the `likes` count for a post based on its ID.  
  - `void commentOnPost(int postId)`
    - Increments the `comments` count for a post based on its ID.  

- **Feed Generation**
  - `vector<Post> getFeed(int userId)`
    - Generates a personalized feed for a user.  
    - **Steps:**
      1. Iterates through all posts.
      2. Calculates a **score** for each post based on:
         - Number of likes and comments.
         - Whether the post is from a friend.
         - Post recency using the `timestamp` attribute.
      3. Ranks posts using a **priority queue**.
      4. Retrieves the top 10 highest-scored posts for the feed.

- **Time Simulation**
  - `int currentTime()`
    - Simulates the current time (hardcoded to `1000` for simplicity).

---

#### 3. **Control Flow**
- The program uses a **menu-driven interface** to interact with the user.
- **Instructions Displayed (Choice 0)**: Explains the available options to the user.
- **Switch Statement**:
  - Based on user input, the corresponding function is invoked:
    - `1`: Establish friendships.
    - `2`: Create posts.
    - `3`: Like posts.
    - `4`: Comment on posts.
    - `5`: View the personalized feed.

---

### **Data Structures in Depth**

1. **`map`**
   - Used in `SocialGraph` to store user friendships.  
   - Provides ordered mapping from user IDs to their friend sets.  

2. **`unordered_set`**
   - Stores friends of a user efficiently, allowing O(1) average-time complexity for insertion and lookup.  

3. **`vector`**
   - Used for sequential storage of posts.  
   - Dynamic resizing makes it suitable for an expanding list of posts.  

4. **`priority_queue`**
   - Used for feed prioritization, ensuring the top posts (based on score) are efficiently retrieved.  

5. **`struct` and `class`**
   - Encapsulate related data (e.g., posts, friendships) and provide clean organization.

---

### **Advantages of Chosen Data Structures**

- **`unordered_set`**
  - Ensures fast insertion and retrieval of friends, making friendship lookups efficient.  

- **`vector`**
  - Allows simple and efficient traversal and storage of posts.  

- **`priority_queue`**
  - Facilitates feed ranking by automatically maintaining a sorted structure based on post scores.  

- **`map`**
  - Ensures ordered storage of user IDs for consistent iteration and debugging.

---

### **Enhancements Over Basic Implementation**

- **Personalization:** 
  - Feed scores are based on interactions and relationships, mimicking real-world social media behavior.  

- **Recency Bias:**
  - Older posts are deprioritized unless they have high interaction.  

- **Scalability:**
  - Efficient data structures make the system scalable for a large number of users and posts.

---

## **Conclusion**

This project combines foundational C++ programming with advanced data structures to simulate the backend of a social media platform. The choice of data structures ensures both efficiency and scalability, while the modular design makes it easy to extend functionalities.
