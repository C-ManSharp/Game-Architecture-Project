# Video Game Architecture Project
This project was created by me as part of an assignment for a 12-week module on a Computer Science course. Please note that some of the code was provided to me by the university. All source code located in the "commands" and "components" folders was created by me. Some of the code in the "header" and "source" folders was created by me. The author is clearly stated in a comment at the top of each header file. The assessment required the following pieces of work: A project containing a small working game that must be built using a simple game engine developed by the university; a very short report evaluating the quality of the code produced, a class diagram that showed the architecture of the game code and a sequence diagram that illustrated dynamic behaviour of one game object, I chose player death. The architecture of the game code had the highest weighting with regards to marks, as a result, that aspect of the project received the most attention. The UML diagrams can be found in the "Diagrams" folder. This was the first game that I had created using a minimalist code-only game engine.

I received the maximum number of marks possible for the diagrams. I was three marks off achieving the maximum marks possible for the architecture of the program.

The horrible pointer code in some of the upate methods was created to fix a memory leak. I discovered this leak hours before the assessment deadline so I had to fix it quickly. The AI for the ships does not work too well. Again, this was due to time constraints.

This project was compiled using Visual Studio 2022 Community Edition.

An old version of DirectX is required to run the project; this is included in the dependencies folder.

Controls:
- W: Move forward
- A: Rotate Left
- D: Rotate Right
- Z: Dodge
- 1 & 2: Change weapon

