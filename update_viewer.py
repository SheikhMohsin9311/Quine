import re

def main():
    try:
        with open("genealogy.dot", "r") as f:
            dot_content = f.read()

        with open("viewer.html", "r") as f:
            html_content = f.read()

        # Regex to find `var DOTstring = ` and the backticked string
        # We assume the format is `var DOTstring = \` ... \`;`
        # We use re.DOTALL to match across newlines
        
        pattern = r"(var DOTstring = `)([^`]*)(`;)"
        
        def replacement(match):
            return match.group(1) + "\n" + dot_content + "\n" + match.group(3)

        new_html = re.sub(pattern, replacement, html_content, flags=re.DOTALL)
        
        with open("viewer.html", "w") as f:
            f.write(new_html)
            
        print("Updated viewer.html with latest genealogy data.")

    except FileNotFoundError:
        print("Error: Could not find genealogy.dot or viewer.html")

if __name__ == "__main__":
    main()
