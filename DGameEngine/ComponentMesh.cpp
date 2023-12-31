#include "ComponentMesh.h"

ComponentMesh::ComponentMesh(shared_ptr<Mesh> mesh_) {
    this->mesh = mesh_;
}

void ComponentMesh::update() {
    if (this->GetIsActive()) {
        mesh->draw();
    }
}