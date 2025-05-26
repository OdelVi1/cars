# cars
gta like C++ game
1.	Title: 2nd Year, 2nd Semester Project - Computer Game In C++ OOP 2nd Course

2.	General Game Explanation:
•	Game based on Grand Theft Auto (GTA)
•	Player's goal: accumulate points, complete missions, and reach destinations
•	Takes place in a city environment
•	Screen displays partial map view centered on the main player
Technical Implementation:
•	Built using inheritance and polymorphism
•	Uses SFML graphics library
•	Implements exception handling (see Exceptions.h class)
Design Patterns Used:
•	Singleton Pattern: 
o	Graphics class
•	State Pattern: 
o	State base class with inheriting classes: RoadState, TakenCarState, PlayerState, PlayerManState, PlayerCar
o	Changes player state (person ↔ car transformation)
o	Changes car state (automatic driving ↔ player control)
•	Factory Pattern: 
o	Generic creation of different gift types with varying production strategies
o	Creates different car types
o	Generates missions tailored to each of the three levels
o	Easy to extend with new objects
•	Observer Pattern: 
o	Missions, score, lives, and fuel register with the player for updates
•	Strategy Pattern: 
o	Changeable movement strategies (see DirectionStrategy class)
o	Currently implements a random direction for cars
o	Ready for future police AI strategies
Additional Features:
•	Uses overloading
•	Implements collision handling using MULTIMETHODS

										
3. List of Files Created:
cars folder
•	Contains all car-related classes in the game
•	Car inheritance enables factory registration (self-registering)
•	Car images stored at specific vector locations
directions folder
•	Responsible for car movement logic
•	Implements Strategy design pattern
game_status folder
•	Game status secondary menu
•	Manages fuel, lives, and score classes
gifts folder
•	Contains the various gift implementations
observers folder
•	Contains classes for update notifications
FullMap class
•	Manages the visual representation of the entire map
CollisionHandling class
•	Responsible for collision detection and handling
Game class
•	Serves as the main game controller
Graphics class
•	Singleton class for graphics and sounds
Level class
•	Manages each individual game level
Menu class
•	Main menu implementation
Moveable class
•	Base class responsible for movements
•	Player and CarRectBase inherit from it
Play class
•	New game start button implementation
Player class
•	Player character class
Junction class
•	Manages road junctions
•	Handles adding/removing junctions from vector
•	Controls junction entrance opening/closing
ObjectFactory class
•	Enables easy object creation
•	Facilitates future object additions
PartialMap class
•	Responsible for map view functionality
Road class
•	Creates nodes that function as roads
•	Manages junctions
4. Main Data Structures and Their Roles: Use of STL data structures and algorithms:
•	Ordered_map in factory to hold what I want to create with a lambda function.
•	unordered_map in the roads.h class is shared_ptr<RoadNode> and it must be of type shared_ptr because each node holds its neighbors to know where it's allowed to drive.
•	Vector in the roads.h class - junctions and their entrances are stored there. And many other simple vectors.
•	STL's find algorithm used to find cars at junctions.



5. Notable Algorithms:
•	Algorithm for finding neighbors of each node where each node has a direction. The algorithm is based on BFS. A neighbor is defined as one whose node direction leads to it, not from it.
•	"Traffic light" system at junctions where the junction is open only in one direction for a timed period and then another entrance opens if time has passed and the junction is also free.
•	Algorithm for maintaining distance between cars. Each car has a buffer in its bumper section so it may maintain distance, and this also works according to the car's speed - if the speed is low it can get closer to objects compared to when it's at high speed and maintains a greater distance.
•	View: The screen displays part of the map, the part where the main player is located. In the center of the board within a certain range the player actually moves. In another range it will appear that he's moving but actually the background will move and not him.
•	There is zoom-in and zoom-out.
•	After the player leaves a car voluntarily, if the car is very close to the road it will know to search for the nearest node and return to driving after several seconds.
6. Known Bugs: None.
7. Other Notes:
•	You can steal a car when the player is adjacent to it, by pressing the space key. a. The car has a fuel meter that can run out, and when it runs out the player is ejected from the car. b. If the car is found on the road it can continue driving normally even if the fuel runs out for the player. c. Each car starts with a random fuel level but remembers how much it had if the player already drove it.
•	Animation for player walking is implemented in toggleMove in the PlayerState class.
•	There are 3 levels - each level contains a mission with more than one target. a. First level - i. The player must collect $10,000. Each coin = $1,000. ii. Then he must go to the police station and pay bail. Upon "collision" with the police station the level ends. b. Second level - i. Must collect a cone-shaped package from the large parking lot. ii. Must reach the lake shore to the red flag. Upon "collision" with it the mission will be declared as successful. c. Third level - i. Must steal a red car and reach the sports field area with it. ii. Must steal a yellow car and reach the sports field area with it. iii. Must steal a police car and reach the sports field area with it. iv. Must steal a Lamborghini and reach the helicopter pad area near the sports field with it. Note that the fuel for each car runs out and if the Lamborghini's fuel (there is only one Lamborghini in the game) runs out before reaching the pad, it won't be possible to win the mission unless he collects $30,000 like every level.


8. Compilation and Execution:
Run with cmake and build gta.exe.
Exit the game back to the menu using the Esc key. To exit the menu completely, you can press Alt, F4 together.

