import json
import subprocess

ENCODING = 'utf-8'
VCPKG_FILE = 'vcpkg.json'
VCPKG_CFG_FILE = 'vcpkg-configuration.json'
VCPKG_URL = r'https://github.com/microsoft/vcpkg.git/'
VCPKG_COLORGLASS_URL = r'https://gitlab.com/colorglass/vcpkg-colorglass.git/'


def get_latest_baseline_commit(url: str, refs: str) -> str:
    process = subprocess.Popen(f'git ls-remote {url} {refs}',
                               stdout=subprocess.PIPE,
                               stderr=subprocess.DEVNULL,
                               encoding=ENCODING,
                               text=True,
                               shell=False)

    while process.poll() is None:
        if line := process.stdout.readline().strip():
            commit, _ = line.split()
            return commit

    return ''


def run() -> None:
    if commit := get_latest_baseline_commit(VCPKG_URL, 'master'):
        with open(VCPKG_FILE, encoding=ENCODING) as f:
            data = json.load(f)

        if data['builtin-baseline'] != commit:
            data['builtin-baseline'] = commit

            with open(VCPKG_FILE, encoding=ENCODING, mode='w') as f:
                json.dump(data, f, indent=2)

    if commit := get_latest_baseline_commit(VCPKG_COLORGLASS_URL, 'main'):
        with open(VCPKG_CFG_FILE, encoding=ENCODING) as f:
            data = json.load(f)

        if data['registries'][0]['baseline'] != commit:
            data['registries'][0]['baseline'] = commit

            with open(VCPKG_CFG_FILE, encoding=ENCODING, mode='w') as f:
                json.dump(data, f, indent=2)


if __name__ == '__main__':
    run()
