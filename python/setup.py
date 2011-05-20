from distutils.core import setup

setup(name='SndObj',
      version='2.6.99',
      description='SndObj Library',
      author='Victor Lazzarini',
      author_email='Victor.Lazzarini@nuim.ie',
      url='http://sndobj.sourceforget.net',
      packages=['sndobj'],
      package_data={'sndobj': ['*.pyd', '*.dll', '*.lib', '*.exp']},
     )

