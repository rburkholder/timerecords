#!/bin/bash
# needs to be similar to args in .vscode/launch.json
../build/AppTimeRecords/AppTimeRecords "--docroot=web;/favicon.ico,/resources,/style,/image" --http-address=0.0.0.0 --http-port=8082 --config=etc/wt_config.xml
