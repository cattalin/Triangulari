using namespace std;
#include "program.h"
#include <fstream>

void set_mesh_clockwise(List *Mesh);
float* program::mesh;
float* program::final_draw;
bool odata = true;
void program::Triangulate(float *input) {
	//fstream input_file("input.txt");
	float temp1,temp2;
	List Mesh, Ears, Reflexes;
	Node* first_node;
	Node* current;
	int points = input[0];
	if (odata)
	{
		odata = false;
		program::final_draw = new float[(points-2)*3*3*2 + 1];
	}
	for (int i = 0; i < points; i++)
		Mesh.push_back(input[i * 2 + 1], input[i * 2 + 2]);
	set_mesh_clockwise(&Mesh);
	/*while (input_file >> temp1)
	{
		points+=1;
		input_file >> temp2;
		Mesh.push_back(temp1, temp2);
	}*/

	mesh = new float[points * 3 + 1];

	first_node = Mesh.peak(1);
	current = Mesh.peak(1);



	//CREATE THE REFLEX ANGLES LIST
	do {
		if (is_reflex(current->get_prev(), current, current->get_next()))
		{
			Reflexes.push_back(current);
		}
		current = current->get_next();
	} while (current != first_node);
	first_node = Mesh.peak(1);
	current = Mesh.peak(1);
	Node *first_reflex = Reflexes.peak(1);
	Node *current_reflex = Reflexes.peak(1);

	//CREATE THE EARS LIST
	do {
		first_reflex = Reflexes.peak(1);
		current_reflex = Reflexes.peak(1);
		bool ureche = true;
		do {
			if (is_reflex(current->get_prev(), current, current->get_next()))
				ureche = false;
			if(current_reflex->get_target()!= current && current_reflex->get_target() != current->get_next() && current_reflex->get_target() != current->get_prev())
				if(is_inside_triangle(current,current->get_prev(),current->get_next(),current_reflex->get_target()))
					ureche = false;
			current_reflex = current_reflex->get_next();
		} while (current_reflex != first_reflex && ureche);
		if (ureche)
			Ears.push_back(current);
		current = current->get_next();
	} while (current != first_node);

	//cout << current->get_coord_x() << current->get_coord_y();
	//float mesh[1000];
	int indice = 1;
	Node *current_ears;
	//mesh[0] = (Mesh.Size() - 2)*3;
	while(Mesh.Size() > 3)
	{//Make triangle
		current_ears = Ears.peak(1);
		current = current_ears->get_target();
		Ears.pop(current_ears);
		Node *left, *right;
		left = current->get_prev();
		right = current->get_next();
		mesh[indice++] = current->get_coord_x();
		mesh[indice++] = current->get_coord_y();
		mesh[indice++] = 0;

		mesh[indice++] = left->get_coord_x();
		mesh[indice++] = left->get_coord_y();
		mesh[indice++] = 0;

		mesh[indice++] = right->get_coord_x();
		mesh[indice++] = right->get_coord_y();
		mesh[indice++] = 0;
		Mesh.pop(current);
		//check if reflex is no longer reflex
		if (!is_reflex(left->get_prev(), left, left->get_next())) {
			first_reflex = Reflexes.peak(1);
			current_reflex = Reflexes.peak(1);
			do {
				if (Reflexes.Size()>0)
				if (current_reflex->get_target() == left) {
					Node* temp=current_reflex->get_prev();
					Reflexes.pop(current_reflex);
					current_reflex = temp;
				}
				if (Reflexes.Size()>0)
				current_reflex = current_reflex->get_next();
			} while (current_reflex != first_reflex);
		}
		//check if reflex is no longer reflex
		if (!is_reflex(right->get_prev(), right, right->get_next())) {
			first_reflex = Reflexes.peak(1);
			current_reflex = Reflexes.peak(1);
			do {
				if(Reflexes.Size()>0)
				if (current_reflex->get_target() == right) {
					Node* temp = current_reflex->get_prev();
					Reflexes.pop(current_reflex);
					current_reflex = temp;
				}
				if (Reflexes.Size()>0)
				current_reflex = current_reflex->get_next();
			} while (current_reflex != first_reflex);
		}
		bool ureche = true;
		if (Reflexes.Size()> 0)
		{
			do {
				if (is_reflex(left->get_prev(), left, left->get_next()))
					ureche = false;
				if (current_reflex->get_target() != left && current_reflex->get_target() != left->get_next() && current_reflex->get_target() != left->get_prev())
					if (is_inside_triangle(left, left->get_prev(), left->get_next(), current_reflex->get_target()))
						ureche = false;
				current_reflex = current_reflex->get_next();
			} while (current_reflex != first_reflex && ureche);
		}
		if (ureche) {
			bool corect = false;
			Node *current_ear_l=Ears.peak(1);
			Node *first_ear_l = Ears.peak(1);
			do {
				if (current_ear_l->get_target() == left) {
					corect = true;
				}
				current_ear_l = current_ear_l->get_next();
			} while (current_ear_l != first_ear_l);
			if (!corect)
			{
				Ears.push_back(left);
			}
		}
		else {
			Node *current_ear_l = Ears.peak(1);
			Node *first_ear_l = Ears.peak(1);
			do {
				if (current_ear_l->get_target() == left) {
					current_ear_l = current_ear_l->get_prev();
					Ears.pop(current_ear_l->get_next());
				}
				current_ear_l = current_ear_l->get_next();
			} while (current_ear_l != first_ear_l);
		}

		ureche = true;
		if (Reflexes.Size() > 0)
		{
			do {
				if (is_reflex(right->get_prev(), right, right->get_next()))
					ureche = false;
				if (current_reflex->get_target() != right && current_reflex->get_target() != right->get_next() && current_reflex->get_target() != right->get_prev())
					if (is_inside_triangle(right, right->get_prev(), right->get_next(), current_reflex->get_target()))
						ureche = false;
				current_reflex = current_reflex->get_next();
			} while (current_reflex != first_reflex && ureche);
		}

		if (ureche) {
			bool corect = false;
			Node *current_ear_l = Ears.peak(1);
			Node *first_ear_l = Ears.peak(1);
			do {
				if (current_ear_l->get_target() == right) {
					corect = true;
				}
				current_ear_l = current_ear_l->get_next();
			} while (current_ear_l != first_ear_l);
			if (!corect)
			{
				Ears.push_back(right);
			}
		}
		else {
			Node *current_ear_l = Ears.peak(1);
			Node *first_ear_l = Ears.peak(1);
			do {
				if (current_ear_l->get_target() == right) {
					current_ear_l = current_ear_l->get_prev();
					Ears.pop(current_ear_l->get_next());
				}
				current_ear_l = current_ear_l->get_next();
			} while (current_ear_l != first_ear_l);
		}
	}
	current_ears = Ears.peak(1);
	current = current_ears->get_target();
	Node *left, *right;
	left = current->get_prev();
	right = current->get_next();
	mesh[indice++] = current->get_coord_x();
	mesh[indice++] = current->get_coord_y();
	mesh[indice++] = 0;

	mesh[indice++] = left->get_coord_x();
	mesh[indice++] = left->get_coord_y();
	mesh[indice++] = 0;

	mesh[indice++] = right->get_coord_x();
	mesh[indice++] = right->get_coord_y();
	mesh[indice++] = 0;
	//cout << is_inside_triangle(current, current->get_next(), current->get_next()->get_next()->get_next(), current->get_next()->get_next());
//	return 0;
	mesh[0] = indice;




}
bool clockwise;
void set_mesh_clockwise(List *Mesh) {
	Node *first_reflex = Mesh->peak(1);
	Node *current_reflex = Mesh->peak(1);
	float sum=0;
	do {
		sum += (current_reflex->get_coord_x() - current_reflex->get_prev()->get_coord_x())*
			(current_reflex->get_coord_y() + current_reflex->get_prev()->get_coord_y());
		current_reflex = current_reflex->get_next();
	} while (current_reflex != first_reflex );
	if (sum < 0)
		clockwise = false;
	else clockwise = true;
}

bool program::is_reflex(Node* p1, Node* p2, Node* p3)
{
	if (get_rotation(p1, p2, p3) >= 0.0f)
		return clockwise;
	return !clockwise;
}
bool program::is_inside_triangle(Node* tr1, Node* tr2, Node* tr3, Node* p)
{
	return (aria(tr1, tr2, tr3) == aria(p, tr1, tr2) + aria(p, tr2, tr3) + aria(p, tr3, tr1));
}
float program::aria(Node* p1, Node* p2, Node* p3)
{
	if ((p1->get_coord_x()*p2->get_coord_y() + p2->get_coord_x()*p3->get_coord_y() + p1->get_coord_y()*p3->get_coord_x() - p3->get_coord_x()*p2->get_coord_y() - p2->get_coord_x()*p1->get_coord_y() - p1->get_coord_x()*p3->get_coord_y())<0)
		return (-((p1->get_coord_x()*p2->get_coord_y() + p2->get_coord_x()*p3->get_coord_y() + p1->get_coord_y()*p3->get_coord_x() - p3->get_coord_x()*p2->get_coord_y() - p2->get_coord_x()*p1->get_coord_y() - p1->get_coord_x()*p3->get_coord_y()) / 2));
	else return (p1->get_coord_x()*p2->get_coord_y() + p2->get_coord_x()*p3->get_coord_y() + p1->get_coord_y()*p3->get_coord_x() - p3->get_coord_x()*p2->get_coord_y() - p2->get_coord_x()*p1->get_coord_y() - p1->get_coord_x()*p3->get_coord_y()) / 2;
}

float program::get_rotation(Node* p1, Node* p2, Node* p3) {//basic orientation test
	float det[9];
	float result = 0;

	det[0] = det[1] = det[2] = 1;
	det[3] = p1->get_coord_x();
	det[6] = p1->get_coord_y();
	det[4] = p2->get_coord_x();
	det[7] = p2->get_coord_y();
	det[5] = p3->get_coord_x();
	det[8] = p3->get_coord_y();

	result = det[0] * det[4] * det[8] + det[2] * det[3] * det[7] + det[1] * det[5] * det[6]
		- (det[2] * det[4] * det[6] + det[1] * det[3] * det[8] + det[0] * det[5] * det[7]);

	return result;
}

