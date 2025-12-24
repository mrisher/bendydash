import oliver_avatar
import naomi_avatar
import daddy_avatar
import mommy_avatar

def to_c_array(name, data):
    lines = []
    lines.append(f"const unsigned char {name}[] = {{")
    for i in range(0, len(data), 16):
        chunk = data[i:i+16]
        hex_chunk = ", ".join([f"0x{b:02x}" for b in chunk])
        lines.append(f"  {hex_chunk},")
    lines.append("}};")
    return "\n".join(lines)

if __name__ == "__main__":
    with open("avatars.h", "w") as f:
        f.write("#ifndef _AVATARS_H_\n#define _AVATARS_H_\n\n")
        f.write(to_c_array("gImage_oliver", oliver_avatar.IMAGE))
        f.write(to_c_array("gImage_naomi", naomi_avatar.IMAGE))
        f.write(to_c_array("gImage_daddy", daddy_avatar.IMAGE))
        f.write(to_c_array("gImage_mommy", mommy_avatar.IMAGE))
        
        f.write("\nconst unsigned char* const Avatar_Images[] = {\n")
        f.write("    gImage_oliver,\n")
        f.write("    gImage_naomi,\n")
        f.write("    gImage_daddy,\n")
        f.write("    gImage_mommy\n")
        f.write("};\n\n")
        
        f.write("const char* const Avatar_Names[] = {\n")
        f.write("    \"Oliver\",\n")
        f.write("    \"Naomi\",\n")
        f.write("    \"Daddy\",\n")
        f.write("    \"Mommy\"\n")
        f.write("};\n\n")
        
        f.write("#endif\n")
