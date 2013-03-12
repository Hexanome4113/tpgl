#!/usr/bin/env python
# -*- coding:utf-8 -*-

tree = {
    "elementName": "elem",
    "nodeType": "xml",
    "children": [
        {
            "elementName": "titre",
            "nodeType": "xml",
            "children": [
                {
                    "nodeType": "text",
                    "content": "Hello world"
                }
            ]
        },
        {
            "elementName": "p",
            "nodeType": "xml",
            "children": [
                {
                    "nodeType": "text",
                    "content": "Coucou "
                },
                {
                    "elementName": "b",
                    "nodeType": "xml",
                    "children": [
                        {
                            "nodeType": "text",
                            "content": "sava?"
                        }
                    ]
                }
            ]
        },
        {
            "elementName": "p",
            "nodeType": "xml",
            "children": [
                {
                    "nodeType": "text",
                    "content": "plop"
                }
            ]
        }
    ]
}
