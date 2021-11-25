#include "Event.h"

Event::Event(Device dvc, Type tp, int ID, ButtonState val) : device(dvc), type(tp), id(ID), binary(val), analog(0.0f) {}
Event::Event(Device dvc, Type tp, int ID, float val) : device(dvc), type(tp), id(ID), binary(Event::Rise), analog(val) {}
Event::Event(Device dvc, Type tp, int ID, const Vector &val) : device(dvc), type(tp), id(ID), binary(Event::Rise), analog(0.0f), vector(val) {}
Event::Event(const Event &copy) : device(copy.device), type(copy.type), id(copy.id), binary(copy.binary), analog(copy.analog), vector(copy.vector) {}
