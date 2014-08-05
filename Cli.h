#ifndef CLI_H
#define CLI_H

class Cli
{
private:
    static int state;

    static void ShowMenu(int opt = 0);
    static void ShowMainMenu();
    static void ShowHTTPReq();
    static void ShowStoreHTTPReq();

public:
    static void UseCli();
};

#endif
