#include "NDSelectorTask.h"
#include <algorithm>
#include <chrono>

NDSelectorTask::NDSelectorTask(int i_id, std::vector<Task*> i_children) :
    lastRunning(nullptr)
{
    id = i_id;
    children = i_children;

    for (int i = 0; i < children.size(); i++)
    {
        randomList.push_back(i);
    }

    auto rd = std::random_device{};
    rng = std::default_random_engine{ rd() };
}

//This is very close to the regular selector, just with the shuffle on open.
Status NDSelectorTask::run(Tick* t)
{
    if (status == Status::none)
    {
        t->open(this);
        status = Status::running;
        
        //We only want to shuffle when we first open, not every time
        //This keeps it consistent while the node is going, so it will visit all children
        std::shuffle(randomList.begin(), randomList.end(), rng);
    }

    t->enter(this);
    t->execute(this);

    for (int randIndex : randomList)
    {
        Task* child = children[randIndex];

        if (child->status == Status::none || child->status == Status::running)
        {
            status = child->run(t);

            if (status == Status::running)
            {
                t->exit(this);
                return status;
            }

            if (status == Status::success || status == Status::error)
            {
                t->exit(this);
                t->close(this);
                return status;
            }
        }
    }

    status = Status::failure;
    t->exit(this);
    t->close(this);
    return status;
}
