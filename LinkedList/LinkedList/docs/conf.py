# -- Project information -----------------------------------------------------

project = 'Forward Chaining'
copyright = '2021, Groupe K'
author = 'Groupe K'

# -- General configuration ---------------------------------------------------

extensions = ["breathe"]
breathe_default_project = "BDP"

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# The suffix(es) of source filenames.
# You can specify multiple suffix as a list of string:
#
# source_suffix = ['.rst', '.md']
source_suffix = '.rst'

# The master toctree document.
master_doc = 'index'

exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.

html_theme = 'classic'

html_static_path = ['_static']
