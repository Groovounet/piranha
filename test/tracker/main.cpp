#include "./class.h"
#include <stdio.h>
#include <stdlib.h>

void test1 ()
{
    CClass ();
}

void test2 ()
{
    CClass *p = new CClass;
    delete p;
}

void test3 ()
{
    CClass *p = new CClass [16];
    delete [] p;
}

int main ()
{
    test1 ();
    printf ("Test1 : %d Creaded, %d Deleted, %d Leaks\n", 
        CTracker::Instance ()->Created (TRACKED_CLASS),
        CTracker::Instance ()->Deleted (TRACKED_CLASS),
        CTracker::Instance ()->Leaked (TRACKED_CLASS));
    CTracker::Kill ();

    test2 ();
    printf ("Test2 : %d Creaded, %d Deleted, %d Leaks\n", 
        CTracker::Instance ()->Created (TRACKED_CLASS),
        CTracker::Instance ()->Deleted (TRACKED_CLASS),
        CTracker::Instance ()->Leaked (TRACKED_CLASS));
    CTracker::Kill ();

    test3 ();
    printf ("Test3 : %d Creaded, %d Deleted, %d Leaks\n", 
        CTracker::Instance ()->Created (TRACKED_CLASS),
        CTracker::Instance ()->Deleted (TRACKED_CLASS),
        CTracker::Instance ()->Leaked (TRACKED_CLASS));
    CTracker::Kill ();

    system ("pause");
}
