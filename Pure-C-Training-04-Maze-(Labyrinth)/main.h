int LookForEntrance(void);
void DecisionToMove(int cursorv, int cursorh);
int DeadEndDetect(int cursorv, int cursorh);
int DirectionDetect(int cursorv, int cursorh);
int CheckDown(int cursorv, int cursorh);
int CheckLeft(int cursorv, int cursorh);
int CheckRight(int cursorv, int cursorh);
int CheckUp(int cursorv, int cursorh);
void PrintResult(const int array1[MSIZEX][MSIZEY], int array2[MSIZEX][MSIZEY]);
void CheckTrack(int cursorv, int cursorh);
