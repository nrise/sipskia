#include "SkCanvas.h"
#include "SkCommandLineFlags.h"
#include "SkData.h"
#include "SkDocument.h"
#include "SkGraphics.h"
#include "SkSurface.h"
#include "SkImage.h"
#include "SkImageFilter.h"
#include "SkStream.h"
#include "SkString.h"
#include "SkPaint.h"
#include "SkImageGenerator.h"

#include <boost/python.hpp>
#include <stdexcept>

#define IMAGE_QUALITY 70

#ifdef SIPSKIA_BGRA
#define SIPSKIA_COLORTYPE kBGRA_8888_SkColorType
#else
#define SIPSKIA_COLORTYPE kN32_SkColorType
#endif


boost::python::object convert_original(char* data, long size, bool is_gallery_card) {
	SkBitmap bm;
	sk_sp<SkData> skdata(SkData::MakeWithoutCopy((void*)data, size));
	if(!data) return boost::python::object();
	std::unique_ptr<SkImageGenerator> gen = SkImageGenerator::MakeFromEncoded(skdata);
	if(!gen) return boost::python::object();

	SkImageInfo bmInfo = gen->getInfo();
	gen->tryGenerateBitmap(&bm, bmInfo, nullptr);

	float width = 720.0f;
	float height = 720.0f;
	if(is_gallery_card){
		height = 1120.0f;
	}

	if(bm.width() == (int)width && bm.height() == (int)height) {
		return boost::python::object(boost::python::handle<>(PyString_FromStringAndSize(data, size)));
	}

	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setStyle(SkPaint::kFill_Style);
	paint.setFilterQuality(kHigh_SkFilterQuality);

	sk_sp<SkSurface> surface(SkSurface::MakeRaster(SkImageInfo::Make(width, height, SIPSKIA_COLORTYPE, kPremul_SkAlphaType, nullptr)).release());
	SkCanvas* canvas = surface->getCanvas();
	canvas->drawBitmapRect(bm, SkRect::MakeLTRB(0, 0, width, height), SkRect::MakeXYWH(0.0f, 0.0f, width, height), &paint);
	sk_sp<SkImage> img(surface->makeImageSnapshot());
	if(!img) return boost::python::object();
	sk_sp<SkData> jpg(img->encode(SkEncodedImageFormat::kJPEG, IMAGE_QUALITY));
	if(!jpg) return boost::python::object();

	return boost::python::object(boost::python::handle<>(PyString_FromStringAndSize((char*)jpg->data(), jpg->size())));
}

boost::python::object convert_list(char* data, long size) {
	SkBitmap bm;
	sk_sp<SkData> skdata(SkData::MakeWithoutCopy((void*)data, size));
	if(!data) return boost::python::object();
	std::unique_ptr<SkImageGenerator> gen = SkImageGenerator::MakeFromEncoded(skdata);
	if(!gen) return boost::python::object();

	SkImageInfo bmInfo = gen->getInfo();
	gen->tryGenerateBitmap(&bm, bmInfo, nullptr);

	float width = 720.0f;
	float height = 472.0f;
	float top = (float)bm.height() / 2.0f - height / 2.0f;
	float bottom = top + height;

	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setStyle(SkPaint::kFill_Style);
	paint.setFilterQuality(kHigh_SkFilterQuality);

	sk_sp<SkSurface> surface(SkSurface::MakeRaster(SkImageInfo::Make(width, height, SIPSKIA_COLORTYPE, kPremul_SkAlphaType, nullptr)).release());
	SkCanvas* canvas = surface->getCanvas();
	canvas->drawBitmapRect(bm, SkRect::MakeLTRB(0, top, width, bottom), SkRect::MakeXYWH(0.0f, 0.0f, width, height), &paint);
	sk_sp<SkImage> img(surface->makeImageSnapshot());
	if(!img) return boost::python::object();
	sk_sp<SkData> jpg(img->encode(SkEncodedImageFormat::kJPEG, IMAGE_QUALITY));
	if(!jpg) return boost::python::object();

	return boost::python::object(boost::python::handle<>(PyString_FromStringAndSize((char*)jpg->data(), jpg->size())));
}

boost::python::object convert_reply(char* data, long size) {
	SkBitmap bm;
	sk_sp<SkData> skdata(SkData::MakeWithoutCopy((void*)data, size));
	if(!data) return boost::python::object();
	std::unique_ptr<SkImageGenerator> gen = SkImageGenerator::MakeFromEncoded(skdata);
	if(!gen) return boost::python::object();

	SkImageInfo bmInfo = gen->getInfo();
	gen->tryGenerateBitmap(&bm, bmInfo, nullptr);

	float width = 720.0f;
	float height = 472.0f;
	float top = (float)bm.height()/2.0f - height/2.0f;
	float bottom = top + height;

	float canvas_width = 460.0f;
	float canvas_height = 310.0f;

	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setStyle(SkPaint::kFill_Style);
	paint.setFilterQuality(kHigh_SkFilterQuality);

	sk_sp<SkSurface> surface(SkSurface::MakeRaster(SkImageInfo::Make(canvas_width, canvas_height, SIPSKIA_COLORTYPE, kPremul_SkAlphaType, nullptr)).release());
	SkCanvas* canvas = surface->getCanvas();
	canvas->drawBitmapRect(bm, SkRect::MakeLTRB(0, top, width, bottom), SkRect::MakeXYWH(0.0f, 0.0f, canvas_width, canvas_height), &paint);
	sk_sp<SkImage> img(surface->makeImageSnapshot());
	if(!img) return boost::python::object();
	sk_sp<SkData> jpg(img->encode(SkEncodedImageFormat::kJPEG, IMAGE_QUALITY));
	if(!jpg) return boost::python::object();

	return boost::python::object(boost::python::handle<>(PyString_FromStringAndSize((char*)jpg->data(), jpg->size())));
}

boost::python::object convert_medium(char* data, long size) {
	SkBitmap bm;
	sk_sp<SkData> skdata(SkData::MakeWithoutCopy((void*)data, size));
	if(!data) return boost::python::object();
	std::unique_ptr<SkImageGenerator> gen = SkImageGenerator::MakeFromEncoded(skdata);
	if(!gen) return boost::python::object();

	SkImageInfo bmInfo = gen->getInfo();
	gen->tryGenerateBitmap(&bm, bmInfo, nullptr);

	float width = 720.0f;
	float height = 720.0f;
	float top = (float)bm.height()/2.0f - height/2.0f;
	float bottom = top + height;

	float canvas_width = 360.0f;
	float canvas_height = 360.0f;

	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setStyle(SkPaint::kFill_Style);
	paint.setFilterQuality(kHigh_SkFilterQuality);

	sk_sp<SkSurface> surface(SkSurface::MakeRaster(SkImageInfo::Make(canvas_width, canvas_height, SIPSKIA_COLORTYPE, kPremul_SkAlphaType, nullptr)).release());
	SkCanvas* canvas = surface->getCanvas();
	canvas->drawBitmapRect(bm, SkRect::MakeLTRB(0, top, width, bottom), SkRect::MakeXYWH(0.0f, 0.0f, canvas_width, canvas_height), &paint);
	sk_sp<SkImage> img(surface->makeImageSnapshot());
	if(!img) return boost::python::object();
	sk_sp<SkData> jpg(img->encode(SkEncodedImageFormat::kJPEG, IMAGE_QUALITY));
	if(!jpg) return boost::python::object();

	return boost::python::object(boost::python::handle<>(PyString_FromStringAndSize((char*)jpg->data(), jpg->size())));
}

boost::python::object convert_thumbnail(char* data, long size) {
	SkBitmap bm;
	sk_sp<SkData> skdata(SkData::MakeWithoutCopy((void*)data, size));
	if(!data) return boost::python::object();
	std::unique_ptr<SkImageGenerator> gen = SkImageGenerator::MakeFromEncoded(skdata);
	if(!gen) return boost::python::object();

	SkImageInfo bmInfo = gen->getInfo();
	gen->tryGenerateBitmap(&bm, bmInfo, nullptr);

	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setStyle(SkPaint::kFill_Style);
	paint.setFilterQuality(kHigh_SkFilterQuality);

	float canvas_size = 132.0f;
	float origin_size = 720.0f;
	float top = bm.height() / 2.0f - origin_size / 2.0f;
	float bottom = top + origin_size;

	sk_sp<SkSurface> surface(SkSurface::MakeRaster(SkImageInfo::Make(canvas_size, canvas_size, SIPSKIA_COLORTYPE, kPremul_SkAlphaType, nullptr)).release());
	SkCanvas* canvas = surface->getCanvas();
	canvas->drawBitmapRect(bm, SkRect::MakeLTRB(0, top, origin_size, bottom), SkRect::MakeXYWH(0.0f, 0.0f, canvas_size, canvas_size), &paint);
	sk_sp<SkImage> img(surface->makeImageSnapshot());
	if(!img) return boost::python::object();
	sk_sp<SkData> jpg(img->encode(SkEncodedImageFormat::kJPEG, IMAGE_QUALITY));
	if(!jpg) return boost::python::object();

	return boost::python::object(boost::python::handle<>(PyString_FromStringAndSize((char*)jpg->data(), jpg->size())));
}

using namespace boost::python;
BOOST_PYTHON_MODULE(sipskia)
{
	def("convert_original", &convert_original);
	def("convert_list", &convert_list);
	def("convert_reply", &convert_reply);
	def("convert_medium", &convert_medium);
	def("convert_thumbnail", &convert_thumbnail);
}

