#ifndef BLOCKDATA_H
#define BLOCKDATA_H

#include "commondata.h"
#include "resource.h"
#include "blockmaterial.h"
#include "scene/3d/spatial.h"
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
    Ref<ImageTexture> textures[6];
    Ref<ImageTexture> default_texture;
    String custom_mesh_path;
    Spatial* custom_mesh;
    bool solid;
    bool opaque;
protected:
    static void _bind_methods();
public:
    String custom_data_file_path;
    Dictionary custom_data;
    enum Sides {
        TOP = CommonData::TOP,
        BOTTOM = CommonData::BOTTOM,
        RIGHT = CommonData::RIGHT,
        LEFT = CommonData::LEFT,
        FRONT = CommonData::FRONT,
        BACK = CommonData::BACK
    };

    Ref<ImageTexture> _get_side_texture_in_editor(Sides side);

    void set_custom_mesh_path(String path);
    String get_custom_mesh_path();
    Spatial *get_custom_mesh();
    bool has_custom_mesh();
    Ref<ImageTexture> get_texture(Sides side);
    void set_texture(Sides side, Ref<ImageTexture> texture);
    Ref<ImageTexture> get_default_texture();
    void set_default_texture(Ref<ImageTexture> texture);
    bool is_solid();
    void set_solid(bool value);
    bool is_opaque();
    void set_opqaue(bool value);
    Dictionary get_custom_data_dict();
    void set_custom_data_dict(Dictionary dict);
    void set_custom_data_path(String path);
    String get_custom_data_path();

    BlockData();
};

VARIANT_ENUM_CAST(BlockData::Sides)

#endif // BLOCKDATA_H
