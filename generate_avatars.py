import oliver_avatar
import naomi_avatar
import daddy_avatar
import mommy_avatar
from PIL import Image

def bytes_to_image(data, width, height):
    # Create a new 1-bit image
    img = Image.new('1', (width, height))
    
    bytes_per_row = (width + 7) // 8
    
    for y in range(height):
        for b in range(bytes_per_row):
            byte_index = y * bytes_per_row + b
            if byte_index >= len(data):
                break
            byte = data[byte_index]
            for i in range(8):
                x = b * 8 + i
                if x < width:
                    # In our data, it seems 1 is black and 0 is white?
                    # Or vice versa. Usually EPD data: 1 bit = 1 pixel.
                    # Let's assume standard packing: bit 7 is leftmost.
                    # If bit is 1 -> White, 0 -> Black? Or 1->Black?
                    # EPD_GUI logic: if(temp & 0x80) Paint_SetPixel(..., !Color) else Paint_SetPixel(..., Color)
                    # This implies 1 is "Not Color" (White/Background) and 0 is "Color" (Black/Foreground)
                    # BUT, in generate_small_assets.py I reversed it to match what I thought.
                    # Let's assume the source data is correct (1=Black or whatever).
                    # We just need to preserve the visual.
                    # If bit is set, we set pixel to 1.
                    if (byte >> (7 - i)) & 1:
                        img.putpixel((x, y), 1)
                    else:
                        img.putpixel((x, y), 0)
    return img

def image_to_bytes(img):
    # Ensure 64x87
    if img.size != (64, 87):
        # Resize/Fit
        # Create a white background (1) or black (0)?
        # Let's assume 0 is background (transparent/white) and 1 is foreground.
        # Wait, usually for PIL '1' mode, 0 is black, 1 is white.
        # But for EPD data, it depends on the driver.
        # Let's assume 0 is the "empty" color.
        new_img = Image.new('1', (64, 87), 0) 
        
        # Center the image
        bg_w, bg_h = new_img.size
        img_w, img_h = img.size
        
        # Scale down if larger
        if img_w > bg_w or img_h > bg_h:
            img.thumbnail((bg_w, bg_h), Image.Resampling.LANCZOS)
            img_w, img_h = img.size
            
        offset = ((bg_w - img_w) // 2, (bg_h - img_h) // 2)
        new_img.paste(img, offset)
        img = new_img

    width, height = img.size
    bytes_per_row = (width + 7) // 8
    data = []
    
    for y in range(height):
        for b in range(bytes_per_row):
            byte = 0
            for i in range(8):
                x = b * 8 + i
                if x < width:
                    pixel = img.getpixel((x, y))
                    if pixel: # If pixel is set (1)
                        byte |= (1 << (7 - i))
            data.append(byte)
    return data

def to_c_array(name, data):
    lines = []
    lines.append(f"const unsigned char {name}[] = {{")
    for i in range(0, len(data), 16):
        chunk = data[i:i+16]
        hex_chunk = ", ".join([f"0x{{b:02x}}" for b in chunk])
        lines.append(f"  {hex_chunk},")
    lines.append("}};")
    return "\n".join(lines)

def process_avatar(name, data, src_w, src_h):
    print(f"Processing {name}: {src_w}x{src_h}")
    img = bytes_to_image(data, src_w, src_h)
    new_data = image_to_bytes(img)
    print(f"  -> Converted to {len(new_data)} bytes")
    return to_c_array(name, new_data)

if __name__ == "__main__":
    with open("avatars.h", "w") as f:
        f.write("#ifndef _AVATARS_H_\n#define _AVATARS_H_\n\n")
        
        # Oliver: 64x87 (Already correct)
        f.write(process_avatar("gImage_oliver", oliver_avatar.IMAGE, 64, 87))
        
        # Naomi: 68x93
        f.write(process_avatar("gImage_naomi", naomi_avatar.IMAGE, 68, 93))
        
        # Daddy: 47x64
        f.write(process_avatar("gImage_daddy", daddy_avatar.IMAGE, 47, 64))
        
        # Mommy: 48x84
        f.write(process_avatar("gImage_mommy", mommy_avatar.IMAGE, 48, 84))
        
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
