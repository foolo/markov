project('markov', 'cpp')

commonSrc = [
	'src/applib/MarkovState.cpp',
	'src/applib/TextBank.cpp',
	'src/applib/MarkovChain.cpp',
	'src/applib/Dictionary.cpp',
	'src/applib/Util.cpp',
	'src/applib/FileReader.cpp',
	'src/applib/util/ParameterParser.cpp',
	'src/applib/util/Timer.cpp',
	'src/applib/util/SerializeUtils.cpp',
	'src/applib/Generator.cpp',
	'src/applib/StateRange.cpp',
	'src/applib/TextRenderer.cpp',
]

appSrc = commonSrc + ['src/main.cpp']
unittestSrc = commonSrc + ['src/unittest/unittestmain.cpp', 'src/unittest/UnitTests.cpp']

incdirs = include_directories('src', 'src/applib')

appExe = executable('markov', appSrc, include_directories: incdirs)
unittestExe = executable('unittests', unittestSrc, include_directories: incdirs)
test('simple test', unittestExe)
