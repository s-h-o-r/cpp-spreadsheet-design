#pragma once

#include "common.h"
#include "formula.h"
#include "sheet.h"

#include <optional>
#include <unordered_set>
#include <vector>

class Cell : public CellInterface {
public:
    explicit Cell(Sheet& sheet);
    ~Cell();

    void Set(std::string text);
    void Clear();
    void ResetCache();
    void AddReferenceFrom(Cell* cell);
    void RemoveReferenceFrom(Cell* cell);

    CellInterface::Value GetValue() const override;
    std::string GetText() const override;
    std::vector<Position> GetReferencedCells() const override;

private:
//можете воспользоваться нашей подсказкой, но это необязательно.
    class Impl;
    class EmptyImpl;
    class TextImpl;
    class FormulaImpl;
    std::unique_ptr<Impl> impl_;

    std::unordered_set<Cell*> references_to_;
    std::unordered_set<Cell*> references_from_;
    mutable std::optional<FormulaInterface::Value> cache_;

    const Sheet& sheet_;
};

inline std::ostream& operator<<(std::ostream& output, const CellInterface::Value& value) {
    std::visit(
        [&](const auto& x) {
            output << x;
        },
        value);
    return output;
}
