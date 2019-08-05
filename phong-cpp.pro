TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = externals \
          src

app.depends = externals
