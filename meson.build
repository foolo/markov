project('markov', 'cpp')

commonSrc = [
	'src/MarkovState.cpp',
	'src/TextBank.cpp',
	'src/MarkovChain.cpp',
	'src/Dictionary.cpp',
	'src/Util.cpp',
	'src/FileReader.cpp',
	'src/util/ParameterParser.cpp',
	'src/util/Timer.cpp',
	'src/util/SerializeUtils.cpp',
	'src/Generator.cpp',
	'src/StateRange.cpp',
	'src/TextRenderer.cpp',
]

appSrc = commonSrc + ['src/main.cpp']
unittestSrc = commonSrc + ['test/unittestmain.cpp', 'test/UnitTests.cpp']

incdirs = include_directories('src')

appExe = executable('markov', appSrc, include_directories: incdirs)
unittestExe = executable('unittests', unittestSrc, include_directories: incdirs)
test('simple test', unittestExe)
