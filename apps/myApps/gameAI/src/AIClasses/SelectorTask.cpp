#include "SelectorTask.h"

SelectorTask::SelectorTask(int i_id, std::vector<Task*> i_children)
{
    id = i_id;
    children = i_children;
}

Status SelectorTask::run(Tick* t)
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

            //If the child is running then we need to exit to let the action go through/continue
            if (status == Status::running)
            {
                t->exit(this);
                return status;
            }

            //If we're successful on a child that means we're done
            //Also if we have an error we do the same thing
            if (status == Status::success || status == Status::error)
            {
                t->exit(this);
                t->close(this);
                return status;
            }
        }
    }

    //If all children failed that means we're done. Status should already be failure but setting it just in case
    status = Status::failure;
    t->exit(this);
    t->close(this);
    return status;
}
