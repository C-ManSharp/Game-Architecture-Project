# Video Game Architecture Project
This project was created by me as part of an assignment for a 12-week module on a Computer Science course. Please note that some of the code was provided to me by the university. All source code located in the "commands" and "components" folders was created by me. Some of the code in the "header" and "source" folders was created by me. The author is clearly stated in a comment at the top of each header file. The assessment required the following pieces of work: A project containing a small working game that must be built using a simple game engine developed by the university; a very short report evaluating the quality of the code produced, a class diagram that showed the architecture of the game code and a sequence diagram that illustrated dynamic behaviour of one game object, I chose player death. The architecture of the game code had the highest weighting with regards to marks, as a result, that aspect of the project received the most attention. The UML diagrams can be found in the "Diagrams" folder. This was the first game that I had created using a minimalist code-only game engine.

I received the maximum number of marks possible for the diagrams. I was three marks off achieving the maximum marks possible for the architecture of the program.

Here are some strengths and weaknesses of the software produced. Please note that this is not an exhaustive list:

Some strengths:
- Use of the Factory pattern to separate the concern of creating game objects.
- Made use of dependency injection.
- Component architecture allows other developers to create new game objects without touching the engine code.
- With regards to updating, adding, and deleting game objects the Object Manager is closed for modification.

Some weaknesses:
- Game objects contain one list of components which makes it difficult to determine what component each game object has.
- The heavy use of pointers helped reduce coupling but increased data access time for the CPU. For example, each game object has a list of pointers to components instead of having a list of components.
- There is some coupling between components. For example, the Player Physics Component has a reference to the Health Component.
- Single Responsibility principle has not been adhered to. As an example, the Physics components for each of the game objects are doing far too much work.
- Could have used interfaces that would have helped reduce coupling.
- Could have used the observer pattern which would have reduced dependencies across the entire program.
- The Open closed principle has been violated with regards to the Level Manager. If a developer were to create a new type of game object that had to trigger an event that the Level Manager had to respond to. Then the handleEvent(Event& event) function would need to change.
- Object Pooling could have been used with regards to instantiating new asteroids, enemy ships, and bullets.
- Some of the components such as the AstroidPhysicsComponent clear pointers to other components inside the update method. Destroying references to other objects could have been handled better.
- The word asteroid is spelled incorrectly throughout the project.

This project was compiled using Visual Studio 2022 Community Edition.

An old version of DirectX is required to run the project; this is included in the dependencies folder.

Controls:
- W: Move forward
- A: Rotate Left
- D: Rotate Right
- Z: Dodge
- 1 & 2: Change weapon

