from PIL import Image, ImageDraw
import math

def to_c_array(name, img):
    # Ensure image is 1-bit
    img = img.convert('1')
    width, height = img.size
    bytes_per_row = (width + 7) // 8
    
    # EPD_ShowPicture logic in EPD_GUI.cpp:
    # if(temp&0x80) Paint_DrawPoint(x+i,y+j,Color,DOT_PIXEL_1X1,DOT_STYLE_DFT);
    # This means if the bit is 1, it draws with the 'Color' (usually BLACK)
    
    # We want 1 for the icon color (BLACK) and 0 for background (WHITE)
    # So if pixel is 0 (Black in Pillow), we set bit to 1.
    
    data = []
    for y in range(height):
        for b in range(bytes_per_row):
            byte = 0
            for i in range(8):
                x = b * 8 + i
                if x < width:
                    pixel = img.getpixel((x, y))
                    if pixel == 0: # Black (Icon)
                        byte |= (1 << (7 - i))
            data.append(byte)

    s = f"const unsigned char {name}[] = {{\n"
    for i, b in enumerate(data):
        s += f"0x{b:02x}, "
        if (i + 1) % 12 == 0:
            s += "\n"
    s += "\n";
    return s

def draw_wifi(size):
    img = Image.new('1', (size, size), 1)
    draw = ImageDraw.Draw(img)
    # Draw arcs
    cx, cy = size // 2, size - 2
    # Adjusted radii for 12x12 size
    for r in [size-2, size-5, size-8]:
        if r > 0:
            draw.arc([cx-r, cy-r, cx+r, cy+r], 225, 315, fill=0, width=1)
    # Dot at bottom
    draw.point([cx, cy], fill=0)
    return img

def draw_clear(size):
    img = Image.new('1', (size, size), 1)
    draw = ImageDraw.Draw(img)
    center = size // 2
    r = size // 4
    draw.ellipse([center-r, center-r, center+r, center+r], outline=0, width=2)
    for i in range(8):
        angle = i * 45
        x1 = center + (r+2) * math.cos(math.radians(angle))
        y1 = center + (r+2) * math.sin(math.radians(angle))
        x2 = center + (r+8) * math.cos(math.radians(angle))
        y2 = center + (r+8) * math.sin(math.radians(angle))
        draw.line([x1, y1, x2, y2], fill=0, width=2)
    return img

def draw_clouds(size):
    img = Image.new('1', (size, size), 1)
    draw = ImageDraw.Draw(img)
    draw.ellipse([10, 20, 30, 40], fill=0)
    draw.ellipse([20, 15, 45, 40], fill=0)
    draw.ellipse([35, 20, 55, 40], fill=0)
    draw.rectangle([20, 30, 45, 40], fill=0)
    return img

def draw_rain(size):
    img = draw_clouds(size)
    draw = ImageDraw.Draw(img)
    for x in [15, 25, 35, 45]:
        draw.line([x, 42, x-2, 48], fill=0, width=2)
    return img

def draw_snow(size):
    img = draw_clouds(size)
    draw = ImageDraw.Draw(img)
    for x in [15, 25, 35, 45]:
        draw.text((x, 42), "*", fill=0)
    return img

def draw_thunder(size):
    img = draw_clouds(size)
    draw = ImageDraw.Draw(img)
    draw.polygon([30, 40, 20, 55, 35, 50, 25, 65], fill=0)
    return img

def draw_mist(size):
    img = Image.new('1', (size, size), 1)
    draw = ImageDraw.Draw(img)
    for y in [20, 28, 36, 44]:
        draw.line([10, y, 50, y], fill=0, width=2)
    return img

if __name__ == "__main__":
    with open("small_assets.h", "w") as f:
        f.write("#ifndef _SMALL_ASSETS_H_\n#define _SMALL_ASSETS_H_\n\n")
        
        f.write(to_c_array("gImage_wifi_small", draw_wifi(12)))
        f.write(to_c_array("weather_icon_mist", draw_mist(64)))
        f.write(to_c_array("weather_icon_clouds", draw_clouds(64)))
        f.write(to_c_array("weather_icon_thunder", draw_thunder(64)))
        f.write(to_c_array("weather_icon_clear", draw_clear(64)))
        f.write(to_c_array("weather_icon_snow", draw_snow(64)))
        f.write(to_c_array("weather_icon_rain", draw_rain(64)))
        
        f.write("\nconst unsigned char* const Small_Weather_Icons[] = {\n")
        f.write("    weather_icon_mist,\n")
        f.write("    weather_icon_clouds,\n")
        f.write("    weather_icon_thunder,\n")
        f.write("    weather_icon_clear,\n")
        f.write("    weather_icon_snow,\n")
        f.write("    weather_icon_rain\n")
        f.write("};\n\n")
        
        f.write("#endif\n")