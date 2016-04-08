#ifndef BLOCKDATA_H
#define BLOCKDATA_H

#include "commondata.h"
#include "resource.h"
#include "block_material.h"
#include "scene/resources/texture.h"
#include "scene/resources/material.h"
#include "scene/resources/mesh.h"

class BlockData : public Resource
{
    OBJ_TYPE( BlockData, Resource )
private:
    int hardness;
    Ref<BlockMaterial> block_material;
    Ref<Material> visual_material;
    Ref<Texture> textures[6];
    Ref<Texture> default_texture;
    Ref<Mesh> custom_mesh;
    bool solid;
    bool opaque;
protected:
    static void _bind_methods();
public:
    enum Sides {
        TOP = CommonData::TOP,
        BOTTOM = CommonData::BOTTOM,
        RIGHT = CommonData::RIGHT,
        LEFT = CommonData::LEFT,
        FRONT = CommonData::FRONT,
        BACK = CommonData::BACK
    };
    Ref<Mesh> get_custom_mesh();
    void set_custom_mesh(Ref<Mesh> mesh);
    bool has_custom_mesh();
    Ref<Texture> get_texture(Sides side);
    void set_texture(Sides side, Ref<Texture> texture);
    Ref<Texture> get_default_texture();
    void set_default_texture(Ref<Texture> texture);
    bool is_solid();
    void set_solid(bool value);
    bool is_opaque();
    void set_opqaue(bool value);

    BlockData();
};

VARIANT_ENUM_CAST(BlockData::Sides)

#endif // BLOCKDATA_H
