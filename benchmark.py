# -*- coding: utf-8 -*-
import timeit
import sipskia
from wand.image import Image

f = open('sample_like.jpg')
s = f.read()
f.close()


def crop_image(image_data, size_crop):
    from_width, from_height = (image_data.width, image_data.height)
    to_width, to_height = size_crop

    left = int((from_width - to_width) / 2)
    top = int((from_height - to_height) / 2)
    right = left + to_width
    bottom = top + to_height

    image_data.crop(left, top, right, bottom)

    return image_data


def test_wand():
    image_data = Image(blob=s)
    image_data.compression_quality = 70
    is_gallery_card = False
    image_data_size = (image_data.width, image_data.height)

    image_size = (720, 720)
    if is_gallery_card:
        image_size = (720, 1120)

    if image_size != image_data_size:
        result = image_data.resize(image_size[0], image_size[1])

    with image_data.clone() as img:
        result = img = crop_image(img, (720, 472))

        # 공감전용 카드의 경우 댓글용 이미지를 생성하지 않는다.
        if not is_gallery_card:
            result = img.resize(460, 310)

    result = image_data.resize(360, 360)
    result = image_data.resize(132, 132)
    return result


def test_skia():
    result = sipskia.convert_original(s, len(s), False)
    result = sipskia.convert_list(s, len(s))
    result = sipskia.convert_reply(s, len(s))
    result = sipskia.convert_medium(s, len(s))
    result = sipskia.convert_thumbnail(s, len(s))
    return result


print timeit.timeit(test_wand, number=10)
print timeit.timeit(test_skia, number=10)
