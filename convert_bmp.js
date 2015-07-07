function	convert_bmp(file)
{
    var	ctx;
    var	width;
    var	height;
    var	bmp;

    canvas = documentToImageData("file");
    ctx = canvas.getContext("2d");
    width = file.infoheader.biwidth;
    height = file.infoheader.biheight;
    bmp = ctx.createImageData(width, height);
    return (bmp);
}

function	main()
{
    var	win;

    mlj_init("test");
}
