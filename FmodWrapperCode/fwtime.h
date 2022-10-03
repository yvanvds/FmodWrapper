#pragma once


namespace FW {
	namespace INTERNAL {
        class time {
        public:

            void update(); // called in system update

            float delta();

            time() { _current = _last = 0; _delta = 0.0f; }
        private:
            unsigned long _current;
            unsigned long _last;
            float _delta;
        };

        time& Time();
	}
}