#ifndef CLI_H
#define CLI_H

class Cli
{
private:
    static int state;

    static void ShowMenu(int opt = 0);
    static void ShowMainMenu();
    static void ShowHTTPReq();

public:
    static void UseCli();
};

#endif
