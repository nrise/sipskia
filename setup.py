import distutils.sysconfig
import os
import sys
from setuptools import setup, Extension

# 사용자 경로 설정 부분 시작
skia_include_home_prefix = '/Users/ryukyoungmook/skia'
skia_lib_dir = '/Users/ryukyoungmook/skia/out/Static'
boost_python_include_dir = '/usr/local/include/'
boost_python_lib_dir = '/usr/local/lib'
if 'linux' in sys.platform:
    skia_include_home_prefix = '/home/ubuntu/skia'
    skia_lib_dir = '/home/ubuntu/skia/out/Static'
    boost_python_include_dir = '/home/ubuntu/boost/include/'
    boost_python_lib_dir = '/home/ubuntu/boost/lib'
# 사용자 경로 설정 부분 끝

module_name = 'sipskia'

if sys.platform == 'darwin':
    libraries = [
        'boost_python3', 'skia',
    ]
else:
    libraries = [
        'boost_python3', 'skia_codec', 'skia_codec_android', 'skia_core',
        'skia_effects', 'skia_images', 'skia_opts', 'skia_opts_avx',
        'skia_opts_avx2', 'skia_opts_sse41', 'skia_opts_sse42',
        'skia_opts_ssse3', 'skia_pdf', 'skia_ports', 'skia_sfnt',
        'skia_skgpu', 'skia_skgputest', 'skia_svg', 'skia_utils',
        'skia_views', 'skia_xml', 'skia_xps',
    ]

extra_link_args = []
if sys.platform == 'darwin':
    extra_link_args = [
                          '-framework', 'OpenGL',
                          '-framework', 'QuartzCore',
                          '-framework', 'Cocoa',
                      ]
else:
    extra_link_args = ['-lskia', '-lboost_python3']
    libraries = []

skia_includes = [
    ('tools', ['gpu', 'flags']),
    ('include', [
        'core', 'c', 'config', 'pathops', 'utils/mac', 'codec', 'android',
        'effects', 'client/android', 'images', 'ports', 'utils', 'gpu',
    ]),
    ('src', ['utils', 'sfnt']),
]

include_dirs = [boost_python_include_dir, ]
for mid_dir, suffix_dirs in skia_includes:
    for suffix in suffix_dirs:
        include_dirs.append('{}/{}/{}'.format(
            skia_include_home_prefix, mid_dir, suffix))

if sys.platform == 'darwin':
    cmd = [
        '-MMD', '-MF', 'sipskia.o.d', '-O3', '-gdwarf-2',
        '-mmacosx-version-min=10.7',
        # '-Werror', '-mmacosx-version-min=10.7',
        '-arch', 'x86_64', '-mssse3', '-Wall', '-Winit-self',
        '-Wpointer-arith', '-Wsign-compare', '-Wno-unused-parameter',
        '-std=c++11', '-stdlib=libc++', '-fvisibility-inlines-hidden',
        '-fno-threadsafe-statics',
    ]
elif 'linux' in sys.platform:
    cmd = [
        '-fPIC', '-MMD', '-MF', 'sipskia.o.d', '-g', '-fno-exceptions',
        '-fstrict-aliasing', '-Wall', '-Wextra', '-Winit-self',
        '-Wpointer-arith', '-Wsign-compare', '-Wno-unused-parameter',
        '-m64', '-Werror', '-O3', '-std=c++11', '-fexceptions',
        '-fno-threadsafe-statics', '-Wnon-virtual-dtor',
        '-Wno-unused-local-typedefs', '-Wno-return-type',
        '-Wno-missing-field-initializers',
    ]

macros = [
    ('SK_INTERNAL', None),
    ('SK_GAMMA_SRGB', None),
    ('SK_GAMMA_APPLY_TO_A8', None),
    ('QT_NO_KEYWORDS', None),
    ('SK_ALLOW_STATIC_GLOBAL_INITIALIZERS', 1),
    ('DSK_SUPPORT_GPU', 1),
    ('SK_FORCE_DISTANCE_FIELD_TEXT', 0),
    ('SK_HAS_GIF_LIBRARY', None),
    ('SK_HAS_JPEG_LIBRARY', None),
    ('SK_HAS_PNG_LIBRARY', None),
    ('SK_HAS_WEBP_LIBRARY', None),
    ('SK_CODEC_DECODES_RAW', None),
    ('SK_SUPPORT_PDF', 1),
]
if sys.platform == 'darwin':
    macros += [
        ('SK_BUILD_FOR_MAC', None),
        ('SK_NDEBUG', 1),
    ]
elif 'linux' in sys.platform:
    macros += [
        ('SK_SAMPLES_FOR_X', None),
        ('SK_BUILD_FOR_UNIX', None),
        ('SK_NDEBUG', None),
        ('SIPSKIA_BGRA', None),
    ]

os.environ.setdefault('CC', 'clang')
os.environ.setdefault('CXX', 'clang++')
orig_customize_compiler = distutils.sysconfig.customize_compiler


def customize_compiler(compiler):
    orig_customize_compiler(compiler)
    compiler.compiler = [os.environ['CC'], ] + cmd
    compiler.compiler_so = [os.environ['CXX'], ] + cmd
    compiler.compiler_cxx[0] = os.environ['CXX']
    compiler.linker_so[0] = os.environ['CXX']
    return compiler


distutils.sysconfig.customize_compiler = customize_compiler

module = Extension(module_name,
                   define_macros=macros,
                   include_dirs=include_dirs,
                   extra_compile_args=[],
                   extra_link_args=extra_link_args,
                   libraries=libraries,
                   library_dirs=[boost_python_lib_dir, skia_lib_dir],
                   sources=['sipskia.cpp'])

setup(name=module_name,
      version='0.0.2',
      description='This is a Simple Image Processing by Skia',
      ext_modules=[module])
