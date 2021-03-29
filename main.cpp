#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
///OPEN GL
#include <GL/glut.h>

/*
    Erik Scholtz
    12/06/2020
    This program will take the input from the files, and then display a map of the usa counties. It also
    displayes the 2012 election demographics now.
*/

using namespace std;

struct point{
    double x; ///for x coordinate
    double y; ///for y coordinate
};
struct county{
    string name; ///name of county
    string abv; ///abreviation of state
    int totalpoints; ///total ammount of points to make county on make
    vector <point> cords; ///vector of points on map
    int vote = 0; ///who won the vote
};
struct name{
    string full; ///full name
    string abvr; ///abreviated name
};
vector <county> counties; ///global vector for the ammount counties
vector <name> county_Name; ///name of the county
double right_border,left_border,top_border,bottom_border; ///for setting the borders for the map

static void key(unsigned char key, int x, int y) { ///get the exit key
    switch (key) {
    case 27 : ///if escape key is pressed
    case 'q': ///if q is pressed
        exit(0); ///exit
        break;
    }
}
void display() { ///for desplaying the map
    glClearColor(1.0,1.0,1.0,1.0); ///sets background colour to white
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho( left_border, right_border, bottom_border, top_border,-1,1); ///sets the border for the map
    glColor3f(0.0,0.0,0.0); ///sets line colour to black
    ///init colouring
    for(int i=0; i<counties.size(); i++) { ///loops for the ammount of counties
        for(int j = 0 ; j < counties[i].totalpoints-1 ; j++) { ///for the ammount of coordinate points of the county
            if(counties[i].vote==1){ ///if Romney wins
                glColor3f(1,0,0); ///red
            }
            else if(counties[i].vote==2){ ///if Obama wins
                glColor3f(0,0,1); ///blue
            }
            else{ ///if anyone else wins
                glColor3f(0,1,0); ///green
            }
            glBegin(GL_LINE_STRIP); ///starts the line for drawing
            glVertex2d(counties[i].cords.at(j).x, counties[i].cords.at(j).y); ///sets the certex point for the line
            glVertex2d(counties[i].cords.at(j+1).x, counties[i].cords.at(j+1).y); ///sets the other vertex point
            glEnd(); ///ends the line
        }
    }
    glFlush(); ///flushes and refreshed screen
}
void input_file(string filename1, string filename2, string filename3){ ///function for reading the file
    int limit; ///limit for amount of lines
    ifstream InFile(filename1.c_str()); ///create ifstream
    if(InFile.fail()) { ///if it fails display message
        cout<<"File not found"<<endl;
    }
    else {
        string line;

        InFile >> left_border; ///get the left bound
        InFile >> bottom_border; ///get the bottom bound
        InFile >> right_border; ///get the right bound
        InFile >> top_border; ///get the top bound
        getline(InFile,line); ///get the line
        while (getline(InFile, line)) { ///while loop for every line
            county temp; ///creates temp vertion of structure
            getline(InFile,line); ///skip a line
            getline(InFile,line); ///skip a line
            temp.name =line; ///grabs the name of county from file
            getline(InFile,line); ///skip a line
            temp.abv = line; ///gets abreveation from file
            InFile >> limit; ///grabs limit from file
            temp.totalpoints = limit; ///sets limit for points for county
            for(int i = 0 ; i < limit ; i++) { ///for the amount of points
                point temp2; ///make a temporary point
                InFile >> temp2.x; ///set the x
                InFile >> temp2.y; ///set the y
                temp.cords.push_back(temp2); ///declare in vector
            }
            counties.push_back(temp); ///declare in vector
        }
    }
    InFile.close(); ///close the map
    ifstream InFileTwo(filename2.c_str()); /// just a text file
    if (InFileTwo.fail()) { ///if file doesent open
        cout << "Unable to open file";
        exit(1); /// terminate with error
    } else { ///if the file opens
        string line;///make a string for the line
        while(getline(InFileTwo,line)) { /// getline returns false at EOF
            string inputStr(line);
            string buf; /// Have a buffer string
            stringstream s(inputStr); /// Insert the string into a stream
            s<<inputStr;///put the line into the stream
            string input;///string for the input
            name temp3; ///make a temp3 for the names
            while (getline(s, input, ',')) { ///gets a string from the stream up the next space
                temp3.full = input; ///set the point to the input
                getline(s, input, ','); ///get the next line
                temp3.abvr = input.substr(1); ///get the next point without the two spaces at the front
            }
            county_Name.push_back(temp3); ///push back the county names
        }
    }
    InFileTwo.close(); ///close the file*/
    ifstream InFileThree(filename3.c_str()); /// just a text file
    if (InFileThree.fail()) { ///if the file doesent open
        cout << "Unable to open file";
        exit(1); /// terminate with error
    } else { ///if the file opens
        bool once = true; ///set once to true
        string line;///make a string for the line
        while(getline(InFileThree,line)) { /// getline returns false at EOF
            string inputStr(line);
            string buf; /// Have a buffer string
            stringstream s(inputStr); /// Insert the string into a stream
            s<<inputStr;///put the line into the stream
            string input;///string for the input
            if(once) { ///if once is true
                getline(s, input, ','); ///get a line
                getline(s, input, ','); ///get a line
                getline(s, input, ','); ///get a line
                getline(s, input, ','); ///get a line
                once = false; ///set once to false
            }
            while (getline(s, input, ',')) { ///gets a string from the stream up the next space
                string state; ///string for the state
                int num1,num2,num3; ///3 nums
                state = input; ///get the state
                s >> num1; ///get number 1
                getline(s, input, ','); ///get the next line
                s >> num2; ///get number 2
                getline(s, input, ','); ///get the next line
                s >> num3; ///get number 3
                if(num1 > num2 && num1 > num3) { ///if number 1 is the greatest
                    for(int i = 0; i<county_Name.size(); i++) { ///for the amount of county names
                        if(state == county_Name[i].full) { ///if the county name equals the state
                            for(int b = 0; b<counties.size(); b++) { ///for the amount of counties
                                if(counties[b].abv == county_Name[i].abvr) { ///if the abbrevation of the county equals the abbrevation of the county name
                                    if(counties[b].vote == 0) { ///if the vote winner is not set yet
                                        counties[b].vote = 1; ///set the vote winner to 1
                                    }
                                }
                            }
                        }
                    }
                }
                if(num2 > num1 && num2 > num3) { ///if number 2 is the greatest
                    for(int i = 0; i<county_Name.size(); i++) { ///for the amount of county names
                        if(state == county_Name[i].full) { ///if the county name equals the state
                            for(int b = 0; b<counties.size(); b++) { ///for the amount of counties
                                if(counties[b].abv == county_Name[i].abvr) { ///if the abbrevation of the county equals the abbrevation of the county name
                                    if(counties[b].vote == 0) { ///if the winner is not set yet
                                        counties[b].vote = 2; ///set the winner to 2
                                    }
                                }
                            }
                        }
                    }
                }
                if(num3 > num1 && num3 > num2) { ///if number 3 is the greatest
                    for(int i = 0; i<county_Name.size(); i++) { ///for the amount of county names
                        if(state == county_Name[i].full) { ///if the county name equals the state
                            for(int b = 0; b<counties.size(); b++) { ///for the amount of counties
                                if(counties[b].abv == county_Name[i].abvr) { ///if the abbrevation of the county equals the abbrevation of the county name
                                    if(counties[b].vote == 0) { ///if the vote winner is not set yet
                                        counties[b].vote = 3; ///set the vote winner to 2
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
int main (int argc, char **argv){
    glutInit( &argc, argv );
    string filename1 = "countiesUSA.txt"; ///name of file for making map
    string filename2 = "stateNames.txt"; ///name of file for state names
    string filename3 = "election2012.txt"; ///name of file election votes
    input_file(filename1,filename2,filename3);
    glutInitDisplayMode(GLUT_RGB); ///set the color space
    glutInitWindowSize(1280, 720); ///set the window size
    glutCreateWindow( "Display Lines" ); ///make the window
    glutDisplayFunc(display); ///display the function display
    glutKeyboardFunc(key); ///get the keyboard function key
    glutMainLoop(); ///run the loop
    return 0;
}
