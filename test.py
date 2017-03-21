import sipskia
import os
import sys

with open('./sample.jpg') as f:
    sample = f.read()

with open('./sample_like.jpg') as f:
    sample_like = f.read()


def test_degradation():
    directory = './output_degradation/'
    if not os.path.exists(directory):
        os.makedirs(directory)

    for i in xrange(5):
        file_name = 'sample_degradation_{:03}'.format(i + 1)
        with open('./{}.jpg'.format(file_name)) as f:
            data = f.read()

        for quality in (70, 80, 85, 90, 95, 99, 100):
            webpdata = sipskia.convert_webp(data, len(data), 0, quality)
            result_jpg = sipskia.convert_original(webpdata, len(webpdata), 100)

            with open('{}{}_{}.webp'.format(directory, file_name, quality), 'w') as f:
                f.write(webpdata)

            with open('{}{}_{}.jpg'.format(directory, file_name, quality), 'w') as f:
                f.write(result_jpg)


def test_convert(io=True):
    directory = './output/'
    if not os.path.exists(directory):
        os.makedirs(directory)

    for data, name in ((sample, 'sample'), (sample_like, 'sample_like')):
        if io:
            print 'convert_webp: {}.jpg...'.format(name)
        webpdata = sipskia.convert_webp(data, len(data), name == 'sample_like', 85)
        if io:
            with open('{}{}.webp'.format(directory, name), 'w') as f:
                f.write(webpdata)

        data_length = len(webpdata)

        if io:
            print 'convert_original: {}.jpg...'.format(name)
        result = sipskia.convert_original(webpdata, data_length, 100)
        if io:
            with open('{}{}_detail.jpg'.format(directory, name), 'w') as f:
                f.write(result)

        if io:
            print 'convert_list: {}.jpg...'.format(name)
        result = sipskia.convert_list(webpdata, data_length, 100)
        if io:
            with open('{}{}_list.jpg'.format(directory, name), 'w') as f:
                f.write(result)

        if io:
            print 'convert_medium: {}.jpg...'.format(name)
        result = sipskia.convert_medium(webpdata, data_length, 100)
        if io:
            with open('{}{}_medium.jpg'.format(directory, name), 'w') as f:
                f.write(result)

        if io:
            print 'convert_reply: {}.jpg...'.format(name)
        result = sipskia.convert_reply(webpdata, data_length, 100)
        if io:
            with open('{}{}_reply.jpg'.format(directory, name), 'w') as f:
                f.write(result)

        if io:
            print 'convert_thumbnail: {}.jpg...'.format(name)
        result = sipskia.convert_thumbnail(webpdata, data_length, 100)
        if io:
            with open('{}{}_thumbnail.jpg'.format(directory, name), 'w') as f:
                f.write(result)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print 'usage: test.py [convert|degradation|leak]'
        exit(0)

    mode = sys.argv[1]
    if mode == 'convert':
        test_convert()
    elif mode == 'degradation':
        test_degradation()
    elif mode == 'leak':
        print 'start to convert infinte...'
        print 'check the memory of this process...'
        print 'if you check done, Ctrl + C to exit.'
        while True:
            test_convert(False)
