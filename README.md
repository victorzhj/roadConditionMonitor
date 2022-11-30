This main branch includes a design document.

This is a QT-project so to use the application, Qt-library and Qt-creator are required. In Qt-creator all user needs to do is to open the pro file in rojekti folder and run the project.
After that the application should open and in the application you can draw the gragh by pressing the button named graph.
As of now the only functionality is to draw a graph where the values are hard coded to show an example on how the application will work but later on user can select what they want to be drawn on the graph.


 The application has only one window that includes these main functionalities:
 -The user can pic one data type, a road and timeline to draw a graph. For Road maintenance data there is also a possibility to search for a spesific type of data but the default is that all data will be fetched. The graph is drawn when the user presses the "Draw a graph"-button.
 -The user can save the picked data, road and timeline (search) by pressing "Save search"-button. The search can be named and it will be saved in the preferences. To do the same search again the user can select the saved search from preference dropdown.
    -The saved preference can be deleted by picking it from the dropdown and pressing "Delete preference"-button.
 -The user can save the drawn graph as a image or as data points with the "Save graph"-button. The user can give the saved graph a name and it can be viewed from the compare dropdown. This is how the user can compare different searchers.
     -The saved graph can be deleted by picking it from the dropdown and pressing "Delete graph"-button.
