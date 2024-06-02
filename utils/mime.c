#include <string.h>

const char *get_mime_type(const char *path)
{
    const char *ext = strrchr(path, '.');
    if (ext == NULL)
        return "application/octet-stream"; // Default binary stream

    if (strcmp(ext, ".html") == 0 || strcmp(ext, ".htm") == 0)
        return "text/html";
    if (strcmp(ext, ".css") == 0)
        return "text/css";
    if (strcmp(ext, ".js") == 0)
        return "application/javascript";
    if (strcmp(ext, ".json") == 0)
        return "application/json";
    if (strcmp(ext, ".png") == 0)
        return "image/png";
    if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0)
        return "image/jpeg";
    if (strcmp(ext, ".gif") == 0)
        return "image/gif";
    if (strcmp(ext, ".svg") == 0)
        return "image/svg+xml";
    if (strcmp(ext, ".ico") == 0)
        return "image/x-icon";
    if (strcmp(ext, ".woff") == 0)
        return "font/woff";
    if (strcmp(ext, ".woff2") == 0)
        return "font/woff2";
    if (strcmp(ext, ".ttf") == 0)
        return "font/ttf";
    if (strcmp(ext, ".eot") == 0)
        return "application/vnd.ms-fontobject";
    if (strcmp(ext, ".otf") == 0)
        return "font/otf";
    if (strcmp(ext, ".mp4") == 0)
        return "video/mp4";
    if (strcmp(ext, ".webm") == 0)
        return "video/webm";
    if (strcmp(ext, ".ogg") == 0)
        return "audio/ogg";
    if (strcmp(ext, ".mp3") == 0)
        return "audio/mpeg";
    if (strcmp(ext, ".wav") == 0)
        return "audio/wav";
    if (strcmp(ext, ".pdf") == 0)
        return "application/pdf";
    if (strcmp(ext, ".zip") == 0)
        return "application/zip";
    if (strcmp(ext, ".rar") == 0)
        return "application/x-rar-compressed";
    if (strcmp(ext, ".tar") == 0)
        return "application/x-tar";
    if (strcmp(ext, ".gz") == 0)
        return "application/gzip";
    return "application/octet-stream"; // Default binary stream
}