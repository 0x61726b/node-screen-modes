{
  'targets': [
    {
      'target_name': 'node-screen-modes',
      'sources': [ 'src/node-screen-modes.cpp' ],
      'include_dirs': [
        '<!(node -e "require(\'nan\')")'
      ],
    }
  ]
}
