#include <UnitTest++/UnitTest++.h>
#include <mounts/Observable.h>
#include <string>

TEST(ObservableTest)
{
	Observable<std::string, int> observable;
	int check = 0;

	// add specific observer
	const int specificObserverId = observable.registerObserver("increment", [&check](const int& step){check += step;});

	observable.notifyObservers("increment", 10);
	CHECK_EQUAL(10, check);

	// add generic observer
	const int genericObserverId = observable.registerObserver([&check](const std::string& notification, const int& step)
	{
		if (notification == "increment")
			check += step;
		else if (notification == "decrement")
			check -= step;
	});

	observable.notifyObservers("increment", 4);
	CHECK_EQUAL(18, check); // 10 + 4 by specific observer + 4 by generic one

	observable.notifyObservers("decrement", 17);
	CHECK_EQUAL(1, check);

	// remove sepcific observer
	observable.unregisterObserver(specificObserverId);
	observable.notifyObservers("increment", 5);
	CHECK_EQUAL(6, check);

	observable.unregisterObserver(specificObserverId);
	observable.notifyObservers("decrement", 6);
	CHECK_EQUAL(0, check);

	// remove generic observer
	observable.unregisterObserver(genericObserverId);
	observable.notifyObservers("increment", 3);
	CHECK_EQUAL(0, check);
}
