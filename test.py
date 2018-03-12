import sipskia
import os


def test():
    print('test begin...')
    directory = './output/'
    if not os.path.exists(directory):
        print('output directory does not exists, create it.')
        os.makedirs(directory)

    for file_name in ('sample', 'sample_like'):
        with open(f'./{file_name}.jpg', 'rb', buffering=0) as f:
            data = f.read()
        print(f'test image: {file_name}')

        for quality in (70, 80, 85, 90, 95, 99, 100):
            print(f'\tset the image quality to {quality}...')
            print(f'\t\tconvert jpg to webp')
            webpdata = sipskia.convert_webp(data, 1000, quality)
            with open(
                    f'{directory}{file_name}_{quality}.webp',
                    'wb', buffering=0) as f:
                f.write(webpdata)

            print(f'\t\tconvert webp to jpg')
            jpg = sipskia.convert_jpg(webpdata, 1000, 100)
            with open(
                    f'{directory}{file_name}_{quality}.jpg',
                    'wb', buffering=0) as f:
                f.write(jpg)

            print(f'\t\tconvert jpg to webp with ratio')
            webp_o = sipskia.convert_origin_webp(data, quality)
            with open(
                    f'{directory}{file_name}_o_{quality}.webp',
                    'wb', buffering=0) as f:
                f.write(webp_o)

            print(f'\t\tresize 720 jpg to webp')
            webpdata = sipskia.convert_webp(data, 720, quality)
            with open(
                    f'{directory}{file_name}_720_{quality}.webp',
                    'wb', buffering=0) as f:
                f.write(webpdata)

            print(f'\t\tresize 360 jpg to webp')
            webpdata = sipskia.convert_webp(data, 360, quality)
            with open(
                    f'{directory}{file_name}_360_{quality}.webp',
                    'wb', buffering=0) as f:
                f.write(webpdata)

            print(f'\t\tresize 132 jpg to webp')
            webpdata = sipskia.convert_webp(data, 132, quality)
            with open(
                    f'{directory}{file_name}_132_{quality}.webp',
                    'wb', buffering=0) as f:
                f.write(webpdata)

            print(f'\t\tcrop list jpg to webp')
            webpdata = sipskia.convert_with_crop_jpg(data, 720, 472, 720, 472, quality)
            with open(
                    f'{directory}{file_name}_crop_720_472_{quality}.jpg',
                    'wb', buffering=0) as f:
                f.write(webpdata)

            print(f'\t\tcrop list jpg to webp')
            webpdata = sipskia.convert_with_crop_jpg(data, 720, 472, 460, 310, quality)
            with open(
                    f'{directory}{file_name}_crop_460_310_{quality}.jpg',
                    'wb', buffering=0) as f:
                f.write(webpdata)

    print('test finish...')


if __name__ == '__main__':
    test()
