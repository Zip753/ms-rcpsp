#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Task.h"
#include <utility>
#include <cstdio>
#include <set>

/**
 * Class that represents the specimen in the scheduling problem.
 */
class Schedule {
public:
    Schedule();
    /**
     * Create schedule using given resource assignment.
     * @param _ires list of resource assignments
     */
    Schedule(int *_ires);

    /**
     * Creates a copy of given Schedule.
     */
    Schedule(Schedule *s);
    ~Schedule();

    /**
     * Calculates fitness function for this specimen.
     * Uses cache variable _fitness to execute only once during object lifetime.
     */
    int fitness();
    void show(bool sh = false);
    void show(FILE *stream);

    /**
     * Size of the genotype.
     */
    int size();

    /**
     * List of resources assigned to corresponding tasks.
     */
    int *ires;

    /**
     * List of start times for each task.
     */
    int *start;

    /**
     * List of relative business for each resource. Used to implement LAXCrossover.
     */
    int *business;

    /**
     * Number of resources capable of performing task at index i.
     * @param i index of the task
     */
    int max_res_count(int i);

    /**
     * Index of resource assigned to the task at index i.
     * @param i index of the task
     */
    int resource(int i);

    /**
     * Checks whether this schedule is equal to the given one.
     * Used to implement clone removal.
     * @param s schedule to compare with
     */
    bool eq(Schedule *s);
private:
    /**
     * Number of tasks.
     */
    int n;

    /**
     * List of tasks to complete. Points to Project::tasks.
     */
    Task** tasks;

    /**
     * Cached fitness value for this specimen.
     */
    int _fitness = -1;

    /**
     * Helper list, used in Schedule::update_start().
     */
    bool *visited;

    /**
     * Constructor hook, to keep constructors DRY.
     * @param create_ires parameter that specifies whether resource list should be allocated.
     */
    void init(bool create_ires);

    /**
     * Recursive function to update start time of a task.
     * @param i index of the task
     */
    void update_start(int i);

    /**
     * Critical path fix procedure.
     */
    void reschedule();

    /**
     * Schedule builder.
     * Builds feasible schedule with no conflicts.
     */
    void fix_all();

    /**
     * Finish time of the task at index i.
     * @param i index of the task
     */
    int finish_time(int i);
};

#endif // SCHEDULE_H
