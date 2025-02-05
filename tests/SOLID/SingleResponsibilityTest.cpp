#include "SingleResponsibility.h"
#include <gtest/gtest.h>

TEST(SingleResponsibility, BadSeparation) {
	Journal journal{ "Dear Diary" };
	journal.addEntry("I ate a bug");
	journal.addEntry("I cried today");
	journal.save("BadSeparationJournal.txt");
}

TEST(SingleResponsibility, GoodSeparation) {
	Journal journal{ "Dear Diary" };
	journal.addEntry("I ate a bug");
	journal.addEntry("I cried today");

	PersistenceManager::save(journal, "GoodSeparationJournal.txt");
}