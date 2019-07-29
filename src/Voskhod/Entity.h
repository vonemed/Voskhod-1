#include "Component.h"

#include <memory>
#include <vector>

namespace Voskhod
{
	class Core; // Forward declare

	class Entity
	{
		friend class Core;

	public:

		void display();
		void tick();
	};
}