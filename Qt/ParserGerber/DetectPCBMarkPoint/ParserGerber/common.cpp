#include "common.h"

#include <QFileDialog>

Common::Common()
{

}

QString Common::GetSelectFolder()
{
    return QFileDialog::getExistingDirectory( nullptr, "select folder");
}

QString Common::GetSelectFile()
{
    return QFileDialog::getOpenFileName( nullptr, "select file");
}
