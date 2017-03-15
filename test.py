import sipskia
import os
import sys

with open('./sample.jpg') as f:
    sample = f.read()

with open('./sample_like.jpg') as f:
    sample_like = f.read()


def test_convert(io=True):
    directory = './output/'
    if not os.path.exists(directory):
        os.makedirs(directory)

    for data, name in ((sample, 'sample'), (sample_like, 'sample_like')):
        if io:
            print 'convert_webp: {}.jpg...'.format(name)
        result = sipskia.convert_webp(data, len(data), name == 'sample_like')
        if io:
            with open('{}{}.webp'.format(directory, name), 'w') as f:
                f.write(result)

        with open('{}{}.webp'.format(directory, name)) as f:
            webpdata = f.read()
        data_length = len(webpdata)

        if io:
            print 'convert_original: {}.jpg...'.format(name)
        result = sipskia.convert_original(webpdata, data_length)
        if io:
            with open('{}{}_detail.jpg'.format(directory, name), 'w') as f:
                f.write(result)

        if io:
            print 'convert_list: {}.jpg...'.format(name)
        result = sipskia.convert_list(webpdata, data_length)
        if io:
            with open('{}{}_list.jpg'.format(directory, name), 'w') as f:
                f.write(result)

        if io:
            print 'convert_medium: {}.jpg...'.format(name)
        result = sipskia.convert_medium(webpdata, data_length)
        if io:
            with open('{}{}_medium.jpg'.format(directory, name), 'w') as f:
                f.write(result)

        if io:
            print 'convert_reply: {}.jpg...'.format(name)
        result = sipskia.convert_reply(webpdata, data_length)
        if io:
            with open('{}{}_reply.jpg'.format(directory, name), 'w') as f:
                f.write(result)

        if io:
            print 'convert_thumbnail: {}.jpg...'.format(name)
        result = sipskia.convert_thumbnail(webpdata, data_length)
        if io:
            with open('{}{}_thumbnail.jpg'.format(directory, name), 'w') as f:
                f.write(result)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print 'usage: test.py [convert|leak]'
        exit(0)

    mode = sys.argv[1]
    if mode == 'convert':
        test_convert()
    elif mode == 'leak':
        print 'start to convert infinte...'
        print 'check the memory of this process...'
        print 'if you check done, Ctrl + C to exit.'
        while True:
            test_convert(False)
