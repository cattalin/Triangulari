#include "Node.h"
#include "List.h"


class program {
public:
	static void Triangulate(float *input);
	static float get_rotation(Node* p1, Node* p2, Node* p3);
	static bool is_inside_triangle(Node* p1, Node* p2, Node* p3, Node* p4);
	static float aria(Node* p1, Node* p2, Node* p3);
	static bool is_reflex(Node* p1, Node* p2, Node* p3);

	static float* mash;
	static float* final_draw;
};


