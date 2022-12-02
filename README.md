The software is started by running main.cpp

This is a QT-project so to use the application, Qt-library and Qt-creator are required. In Qt-creator all user needs to do is to open the pro file in rojekti folder and run the project. Note Qt version should be 6 or higher with QtCharts library downloaded (if it doesnt download automatically help is at https://stackoverflow.com/questions/42867557/how-to-install-qtcharts-on-windows). The recommended OS is windows as mac users might experience some problems. (which stem from mac and not us) Linux is not recommended as the software is not tested on the operating system.


#### The application has only one window that includes these main functionalities: <br />
- The user can **pic one data type, a road and timeline to draw a graph**. For Road maintenance data there is also a possibility to search for a spesific type of data but the default is that all data will be fetched. The graph is drawn when the user presses the *"Draw a graph"*-button.
- Depending on your schedule for the day, you may not want to choose too broad gap between the two dates since some of the APIs require one network request per day and drawing the new graph might take a while
- The user can **save the picked data, road and timeline search** by pressing *"Save search"*-button. The search can be named and it will be saved in the **preferences**. To do the same search again the user can select the saved search from preference dropdown.
  - The saved preference can be deleted by picking it from the dropdown and pressing *"Delete preference"*-button.
- The user can **save the drawn graph** as a image or as data points with the *"Save graph"*-button. The user can give the saved graph a name and it can be viewed from the **compare dropdown**. This is how the user can compare different searchers.
  - The saved graph can be deleted by picking it from the dropdown and pressing *"Delete graph"*-button.
- When user chooses **precipitation** option with forecast set to **0** it won't do anything.