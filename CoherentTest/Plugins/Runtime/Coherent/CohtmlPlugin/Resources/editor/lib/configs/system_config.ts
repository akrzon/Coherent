/**
 *  @module lib/config/system_config
 */

'use strict';

export default function systemConfig() {
    System.config({
        paths: {
            'when': 'vendor/when/when.js',
            'react': 'node_modules/react/umd/react.production.min.js',
            'react-dom': 'node_modules/react-dom/umd/react-dom.production.min.js'
        }
    });
}

