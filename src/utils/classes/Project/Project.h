
#ifndef PROJ_H_
#define PROJ_H_

class Project
{
    public:
        void configWindow();

        void init();

        void close();

        void renderAll();

    private:
        void processGameConfig(std::vector<std::string> inputs);
};

#endif