#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "coordinate.h"

int current_id = 0;

void add_coordinate(Coordinate* list_end, float x, float y) {
    Coordinate* new_coord = new Coordinate;
    new_coord->x = x;
    new_coord->y = y;
    new_coord->coord_id = current_id++;
    new_coord->next = nullptr;
    new_coord->previous = list_end;
    if (list_end) list_end->next = new_coord;
}

void forward_display(Coordinate* list_beginning) {
    Coordinate* temp = list_beginning;
    while (temp) {
        std::cout << "ID: " << temp->coord_id << ", x: " << temp->x << ", y: " << temp->y << "\n";
        temp = temp->next;
    }
}

void backward_display(Coordinate* list_end) {
    Coordinate* temp = list_end;
    while (temp) {
        std::cout << "ID: " << temp->coord_id << ", x: " << temp->x << ", y: " << temp->y << "\n";
        temp = temp->previous;
    }
}

void delete_coordinate(Coordinate* list_beginning, int coord_id_to_delete) {
    Coordinate* temp = list_beginning;
    while (temp && temp->coord_id != coord_id_to_delete) {
        temp = temp->next;
    }
    if (temp) {
        if (temp->previous) temp->previous->next = temp->next;
        if (temp->next) temp->next->previous = temp->previous;
        delete temp;
    }
}

int list_length(Coordinate* list_beginning) {
    int length = 0;
    Coordinate* temp = list_beginning;
    while (temp) {
        ++length;
        temp = temp->next;
    }
    return length;
}

void closest_to(Coordinate* list_beginning, float x, float y) {
    Coordinate* temp = list_beginning;
    Coordinate* closest = nullptr;
    float min_distance = std::numeric_limits<float>::max();
    while (temp) {
        float distance = std::sqrt(std::pow(temp->x - x, 2) + std::pow(temp->y - y, 2));
        if (distance < min_distance) {
            min_distance = distance;
            closest = temp;
        }
        temp = temp->next;
    }
    if (closest) {
        std::cout << "Closest to (" << x << ", " << y << "): ID: " << closest->coord_id << ", x: " << closest->x
                  << ", y: " << closest->y << ", Distance: " << min_distance << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_coordinates>\n";
        return 1;
    }
    
    int num_coords = std::atoi(argv[1]);
    std::srand(static_cast<unsigned>(std::time(0)));

    Coordinate* list_beginning = nullptr;
    Coordinate* list_end = nullptr;

    for (int i = 0; i < num_coords; ++i) {
        float x = static_cast<float>(std::rand() % 100);
        float y = static_cast<float>(std::rand() % 100);
        if (!list_beginning) {
            list_beginning = new Coordinate{x, y, 1, nullptr, nullptr};
            list_end = list_beginning;
        } else {
            add_coordinate(list_end, x, y);
            list_end = list_end->next;
        }
    }

    std::cout << "Forward display:\n";
    forward_display(list_beginning);
    std::cout << "\nBackward display:\n";
    backward_display(list_end);

    std::cout << "\nLength of list: " << list_length(list_beginning) << "\n";

    int delete_id = 2; // Example ID to delete
    std::cout << "\nDeleting coordinate with ID " << delete_id << "\n";
    delete_coordinate(list_beginning, delete_id);
    forward_display(list_beginning);

    float target_x = 30.0, target_y = 50.0; // Example target
    std::cout << "\nFinding closest to (" << target_x << ", " << target_y << "):\n";
    closest_to(list_beginning, target_x, target_y);

    return 0;
}
