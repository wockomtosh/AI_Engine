#include "SequenceTask.h"

SequenceTask::SequenceTask(int i_id, std::vector<Task*> i_children)
{
    id = i_id;
    children = i_children;
}

//Basically the inverse of Selector. Swap success and fail from there
Status SequenceTask::run(Tick* t)
{
    if (status == Status::none)
    {
        t->open(this);
        status = Status::running;
    }

    t->enter(this);
    t->execute(this);
    for (Task* child : children)
    {
        if (child->status == Status::none || child->status == Status::running)
        {
            status = child->run(t);

            if (status == Status::running)
            {
                t->exit(this);
                return status;
            }

            if (status == Status::failure || status == Status::error)
            {
                t->exit(this);
                t->close(this);
                return status;
            }
        }
    }

    status = Status::success;
    t->exit(this);
    t->close(this);
    return status;
}
