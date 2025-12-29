
printer_sources = [
  'src/Canvas.c',
  'src/msc.c'
]

cc = meson.get_compiler('c')
m_dep = cc.find_library('m')

printer_lib = static_library(
  'printer',
  printer_sources,
  dependencies: m_dep,
  include_directories: include_directories('.'),
)

printer_dep = declare_dependency(
  link_with: printer_lib,
  include_directories: include_directories('.'),
)

