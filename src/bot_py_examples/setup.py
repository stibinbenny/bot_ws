from setuptools import find_packages, setup

package_name = 'bot_py_examples'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='user',
    maintainer_email='user@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        'publisher = bot_py_examples.publisher:main',
        'subscriber = bot_py_examples.subscriber:main',
        'service_server = bot_py_examples.service_server:main',
        'service_client = bot_py_examples.service_client:main',
        'Action_server = bot_py_examples.Action_server:main',
        'Action_client = bot_py_examples.Action_client:main',
        'parameter = bot_py_examples.parameter:main',
        'simple_tf_kinematics = bot_py_examples.simple_tf_kinematics:main',

        ],
    },
)
